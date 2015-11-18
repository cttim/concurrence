#include <uC++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//help to record the filter type and option
class help{
public:
  char *type;
  int width;
};


_Coroutine Filter {
  protected:
    static const unsigned char End_Filter = '\377';
    unsigned char ch;
  public:
    void put( unsigned char c ) {
        ch = c;
        resume();
    }
};

//subclass of Filter, read a char and pass it to the next pointer
_Coroutine Reader : public Filter {
	Filter *next;
	istream *is;
    // YOU MAY ADD PRIVATE MEMBERS
	public:
		void main(){
			while(true){
			        *is>>noskipws>>ch;
				if(!is->fail()){
					next->put(ch);
				}
				else{
					// pass end_filter char to the next filter
					next->put(End_Filter);
					break;
				}
			}
		}
		//constructor of reader
    		Reader( Filter *f, istream *i ){
			next = f;
			is = i;
			resume();	
		}
};

//subclass of Filter, cout the ch to the std or into a file
_Coroutine Writer : public Filter {
	ostream *out;
    // YOU MAY ADD PRIVATE MEMBERS
 	public:
		void main(){
			while(true){
				if(ch == End_Filter){
					return;
				}
				*out<<ch;
				//*out<<ch;
				suspend();
			}
		}
    		Writer( ostream *o ){
			out = o;		
		}
};

//subclass of a Filter, convert a char into hex and pass it to the next filter
_Coroutine Hex : public Filter {
	Filter *next; 
	// YOU MAY ADD PRIVATE MEMBERS
	//int counter;
	public:
		void main(){
			while(true){
				int counter = 0;
				while(counter <= 16){
					//cout newline or space
					if(counter%16 == 0 && counter !=0){
						next->put('\n');
						break;
					}
					else if(counter%4 == 0 &&counter !=0){
						next->put(' ');
						next->put(' ');
						next->put(' ');
					}
					else if(counter%2 == 0 && counter !=0){
						next->put(' ');
					}
					counter++;
					if(ch == End_Filter){
						next->put(ch);
						return;
					}
					//convert the char to hex
					int value = ch;
					stringstream stream;
					stream << hex << value;
					string result(stream.str());
					//pass char to the next filter
					if(result.length() == 1){
							next->put('0');
							next->put(result[0]);
							suspend();
					}
					else{
							next->put(result[0]);
							next->put(result[1]);
							suspend();
					}
				}
			}
		}  
    		
		Hex( Filter *f){
			next = f;
		}
};

_Coroutine Cap : public Filter {
	Filter *next;
	public:
		void main(){
			//pass all the space char to the next filter
		        while(isspace(ch)){
			        next->put(ch);
				suspend();
			}
			//convert the first char to upper case
			while(true){
				if(ch == End_Filter){
					next->put(ch);
					return;
				}
				ch = toupper(ch);
				next->put(ch);
				suspend();
				while(true){
					// convert the char after ., ?, ! to uppercase
					if(ch == '.' || ch == '?' || ch == '!'){
						next->put(ch);
						suspend();
						if(isspace(ch)){
							next->put(ch);
							suspend();
							while(isspace(ch)){
							  next->put(ch);
							  suspend();
							}
							break;
						}
					}
					if(ch == End_Filter){
						next->put(ch);
						return;
					}
					next->put(ch);
					suspend();	
				}
			}
		}
	
		Cap(Filter* f){
			next = f;		
		}		

};

//subclass of the Filter, use to eliminate the whitespace
_Coroutine Whitespace : public Filter {
	Filter *next;
	public:
		void main(){
			while(true){
				//eliminate the white space from the beginning
				if(isblank(ch)){
					suspend();
					while(isblank(ch)){
						suspend();
					}
					if(ch == '\n'){
					  next->put(ch);
					  suspend();
					  continue;
					}
				}
				next->put(ch);
				suspend();
				while(true){
					//convert muti spaces into one space
				        if(isblank(ch)){
					        suspend();
						while(isblank(ch)){
							suspend();
						}
						if(ch == '\n'){
							next->put(ch);
							suspend();
							break;
						}
						else{
							if(ch == End_Filter){
								next->put(ch);
								return;
							}
							next->put(' ');
							next->put(ch);
							suspend();
						}
					}
					//newline case
					else if(ch == '\n'){
						next->put(ch);
						suspend();
					        break;
					}
					// normal char case
					else{
						if(ch == End_Filter){
							next->put(ch);
							return;
						}
						next->put(ch);
						suspend();
					}
				}
			}		
		}
		
		Whitespace(Filter *f){
			next = f;
		}
};

_Coroutine Triangle : public Filter {
	Filter *next;
	int width;						//use to print
	public:
		void main(){
			while(true){
				int counter = 1;
				while(counter<=width){
					//print the required format
					for(int j=0; j<(width-counter)/2; j++){
						next->put(' ');
					}
					//pass the char to the next filter
					for(int i=0; i<counter; i++){
						if(isblank(ch)){
							next->put(' ');
							suspend();
						}
						//special case convert newline into space
						else if(ch == '\n'){
							next->put(' ');
							suspend();
						}
						else{
							next->put(ch);
							suspend();				
						}
					}
					next->put('\n');
					counter = counter + 2;
				}
			}
		}
		//constructor of triangle
		Triangle(Filter *f, int w){
			next = f;
			width = w;
		}

};

void uMain::main(){
	istream *is=&cin;
	ostream *os=&cout;

	//list of vector
	vector<help*>typeoption;
	vector<Filter*>filterlist;

	//check filter type, option and error
	for(int i=1; i<argc; i++){
		if(argv[i][0] == '-'){
	    		help *h = new help();
	    		h->type = argv[i];
	    		if(!strcmp(h->type, "-T")){
	      			h->width = atoi(argv[i+1]);
	      			if(h->width%2 == 0){
				cerr<<"only accept odd num"<<endl;
				exit(-1);
	      			}
	      			i++;
	    		}
	    		typeoption.push_back(h);
	  	}
		else{
			//input from file
			if(is == &cin){
				try{
					is = new ifstream(argv[i]);
				}catch(...){
					cerr<<"Error! Could not open file "<<'"'<<argv[i]<<'"'<<endl;
					exit(-1);
				}
			}
			//output to file 
			else if(os == &cout){
				os = new ofstream(argv[i]);
			}
		}
	}	
	
	//initialize the writer filter
	Filter *f = new Writer(os);
	//add it into filter vector
	filterlist.push_back(f);
	
	//construct the pipeline for the input
	//push correct filter into the vector
	for(int i= typeoption.size() - 1; i>=0; i--){
	  if(!strcmp(typeoption[i]->type, "-h")){
	    Hex *hex = new Hex(f);
	    filterlist.push_back(hex);
	    f=hex;
	  }
	  else if(!strcmp(typeoption[i]->type, "-s")){
	    Cap *cap = new Cap(f);
	    filterlist.push_back(cap);
	    f=cap;
	  }
	  else if(!strcmp(typeoption[i]->type, "-w")){
	    Whitespace *white = new Whitespace(f);
	    filterlist.push_back(white);
	    f=white;
	  }
	  else if(!strcmp(typeoption[i]->type, "-T")){
	    Triangle *triangle = new Triangle(f, typeoption[i]->width);
	    filterlist.push_back(triangle);
	    f=triangle;
	  }
	  else{
	    cerr<<"unknown filter "<<typeoption[i]->type<<endl;
	    exit(-1);
	  }
	}
	
	//initialized the reader filter
	//the constructor of reader filter will resume the program
	Reader *reader = new Reader(f,is);
	filterlist.push_back(reader);

	//clean up
	for(int i=filterlist.size()-1; i>=0; i--){
	  delete filterlist[i];
	}

	for(unsigned int i=0; i<typeoption.size(); i++){
	  delete typeoption[i];
	}
	
	if(is != &cin){
		delete is;
	}

	if(os != &cout){
		delete os;
	}
	filterlist.clear();

}
