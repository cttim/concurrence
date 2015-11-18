#include <uC++.h>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <string.h>
using namespace std;

_Coroutine Utf8 {
  public:
    //int flag = 0;                       //flag for error and match
    struct Match {
        unsigned int unicode;
        Match( unsigned int unicode ) : unicode( unicode ) {}
    };
    struct Error {};
  private:
    union UTF8 {
        unsigned char ch;               // character passed by cocaller
#if defined( _BIG_ENDIAN ) || BYTE_ORDER == BIG_ENDIAN    // BIG ENDIAN architecture
        struct {                        // types for 1st utf-8 byte
            unsigned char ck : 1;       // check
            unsigned char dt : 7;       // data
        } t1;
        struct {
            unsigned char ck : 3;       // check
            unsigned char dt : 5;       // data
        } t2;
        struct {
            // YOU FIGURE IT OUT
	    unsigned char ck : 4;	// check
	    unsigned char dt : 4;	// data
        } t3;
        struct {
            // YOU FIGURE IT OUT
	    unsigned char ck : 5;	// check
	    unsigned char dt : 3;	// data
        } t4;
        struct {                        // type for extra utf-8 bytes
            // YOU FIGURE IT OUT
	    unsigned char ck : 2;	// check, should always equal to 10
	    unsigned char dt : 6;	// data, used for unicode
        } dt;
#else                                   // LITTLE ENDIAN architecture
        struct {                        // types for 1st utf-8 byte
            unsigned char dt : 7;       // data
            unsigned char ck : 1;       // check
        } t1;
        struct {
            unsigned char dt : 5;       // data
            unsigned char ck : 3;       // check
        } t2;
        struct {
            // YOU FIGURE IT OUT
	    unsigned char dt : 4;	// check
	    unsigned char ck : 4;	// data
        } t3;
        struct {
            // YOU FIGURE IT OUT
	    unsigned char dt : 3;       // check
            unsigned char ck : 5;       // data
        } t4;
        struct {                        // type for extra utf-8 bytes
            // YOU FIGURE IT OUT
	    unsigned char dt : 6;
	    unsigned char ck : 2;
        } dt;
#endif
    } utf8;
    // YOU MAY ADD PRIVATE MEMBERS
    int flag;
    unsigned int unicode_value;
  public:
    // YOU MAY ADD CONSTRUCTOR/DESTRUCTOR IF NEEDED
    Utf8():unicode_value(0),flag(0){}
    void main(){
	int counter;
	// check if the first byte of the utf8 is valid
	if(utf8.t1.ck == 0){
		counter = 0;
		unicode_value = utf8.t1.dt;
		flag = 1;
	}
	else if(utf8.t2.ck == 0x6){
		counter = 1;
		unicode_value = utf8.t2.dt;
		//flag = 1;
	}
	else if(utf8.t3.ck == 0xe){
		counter = 2;
		unicode_value = utf8.t3.dt;
		//flag = 1;
	}
	else if(utf8.t4.ck == 0x1e){
		counter = 3;
		unicode_value = utf8.t4.dt;
		//flag = 1;
	}
	else{
		flag = 2;
	}
	suspend();
	// check the rest bytes and caculate the unicode
	for(int i = 0; i<counter; i++){
		if(utf8.dt.ck != 0x2){
			flag = 2;
		}
		unicode_value <<= 6;
		unicode_value |= utf8.dt.dt;
		if(i+1 == counter){
			break;
		}
		suspend();	
	}
	// check if the unicode value is valid
	if(counter == 0){
		if(! unicode_value <= 0x7f){
			flag = 2;
		}
	}
	else if(counter == 1){
		if(unicode_value < 0x80 || unicode_value > 0x7ff){
			flag = 2;
		}
	}
	else if(counter == 2){
		if(unicode_value < 0x800 || unicode_value > 0xffff){
			flag = 2;
		}
	}
	else if(counter == 3){
		if(unicode_value < 0x10000 || unicode_value > 0x10ffff){
			flag = 2;
		}
	}
	if(flag == 0){
		flag = 1;
	}
		suspend();
    }
    void next( unsigned char c ) {
        utf8.ch = c;                    // insert character into union for analysis
        resume();
        // if necessary throw Match or Error exception
	if(flag == 2){
		throw Error();
	}
	if(flag == 1){
		throw Match(unicode_value);
	}
    }
	
};

void uMain::main(){
	// take input from cin or file
	istream * infile = &cin;
	if(argc==2){
		try{
			infile = new ifstream (argv[1]);
		}catch(uFile::Failure){
			cout<<"file does not exist"<<endl;
			exit(EXIT_FAILURE);
		}
	}
	if(argc > 2){
		cout<<"wrong num of args"<<endl;
		exit(EXIT_FAILURE);
	}
	string line;
	string::iterator i;
	cout<<hex<<showbase;
	while(getline(*infile, line)){
		int nomatcherror = 0;
		if(line.empty()){
			cout<<" : Warning! Blank Line."<<endl;
			continue;
		}
		Utf8 u;
		cout<<"0x"<<noshowbase;
		for(i = line.begin(); i != line.end(); i++){
		  cout << hex << (unsigned int)(unsigned char)*i << noshowbase;
			try{
				u.next(*i);
			}catch(Utf8::Error e){
				nomatcherror = 1;
				cout<<" : invalid" << showbase;
				break;
			}catch(Utf8::Match m){
				nomatcherror = 1;
				cout<<" : valid 0x" << noshowbase << m.unicode;
				break;
			}
		}
		if(nomatcherror == 0){
			cout<<" : invalid";
		}
		else{
			i++;
			if(i != line.end()){
				cout<<". Extra characters ";
				while(i != line.end()){
			  		cout << hex <<(unsigned int) (unsigned char) *i<<noshowbase;
					i++;
				}
			}
		}
		cout<<endl;      	
	}
	if(infile != &cin){
		delete infile;
	}
}



