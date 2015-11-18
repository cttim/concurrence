#include <iostream>
#include <sstream>
#include <fstream>
#include "q1mergesort.h"
#include <cstdlib>
using namespace std;

//set stack size
unsigned int uDefaultStackSize(){
		return 512*1000;
}

//usage message
void usage(char *argv[]){
	cerr<< "Usage: " << argv[0];
	cerr<<" ( -s unsorted-file [ sorted-file ] | -t size (>= 0) [ depth (>= 0) ] )" <<endl;
	exit(EXIT_FAILURE);
}

void uMain::main(){
	istream *infile = &cin;
	ostream *outfile = &cout;	
	int size = 0;
	int depth = 0;

	//parse command line and do error checking
	if(argc <= 2){
		usage(argv);
	}
	string ar = argv[1];
	//check option
	if(ar == "-s"){
		switch (argc) {
			case 3:
				try{
					infile = new ifstream(argv[2]);
				} catch(uFile::Failure){
					usage(argv);
				}
				break;
			case 4:
				try{
					infile = new ifstream(argv[2]);
				} catch(uFile::Failure){
					//cout<<"catch1"<<endl;
					usage(argv);
				}
				
				try{
					//cout<<"enter try2"<<endl;
					outfile = new ofstream(argv[3]);
				} catch(uFile::Failure){
					//cout<<"catch2"<<endl;
					usage(argv);
				}
				break;
			default:
				//cout<<"default"<<endl;
				usage(argv);
		}
			
	}
	else if(ar == "-t"){
		if(argc != 3 && argc !=4){
			usage(argv);
		}
		size = atoi(argv[2]);

		if(size < 0){
		  usage(argv);
		}

		if(argc == 4){
		  depth = atoi(argv[3]);
		}
		
		if(depth < 0){
		  usage(argv);
		}
	}

	else{
		usage(argv);	
	}
	//set uprocessor
	uProcessor p[(1<<depth) - 1] __attribute__ ((unused));
	
	//option t ans start the mergesort task
	if(ar == "-t"){
	  //initialize the unsorted array
	  int *unsort1 = new int[size];
	  for(int i=0; i<size; i++){
	    unsort1[i] = size-i;
	  }
	  //start the task
	  {Mergesort<int> mergetime(unsort1, 0, size-1, depth);}
	  delete unsort1;
	  return;
	}

	//option s

	//declare an string use to parse the input file
	string in;
	TYPE elem;
	for(;;){
	  //start to parse the input file
		*infile>>in;
		if(infile->fail()) break;
		istringstream iss1(in);
		//get the len of the list
		int len;
		iss1 >> len;
		if(len == 0){
			*outfile<<endl<<endl<<endl;
			continue;
		}
		//initialize the unsorted array
		TYPE *unsort = new TYPE[len];
		for(int i=0; i<len; i++){
			*infile>>elem;
			if(infile->fail()) {
				cerr<<"expect have "<<len<<" numbers, but only have "<<i-1<<endl;
				exit(EXIT_FAILURE);
			}
			//istringstream iss2(in);
			//int number;
			//iss2>>number; 
			unsort[i] = elem;
		}
		//print the unsorted array
		for(int k=0; k<len; k++){
			if(k%22 == 0 && k != 0){
				*outfile<<endl<<"  ";
			}
			*outfile<<unsort[k]<<" ";
		}
		*outfile<<endl;
		//start the mergesort task
		{Mergesort<TYPE> me(unsort, 0, len-1, depth);}
		//mergesort finished

		//print the array after sorting
		for(int i=0; i<len; i++){
			if(i%22 == 0 && i != 0){
				*outfile<<endl<<"  ";
			}
			*outfile<<unsort[i]<<" ";
		}
		*outfile<<endl<<endl;

		//clear the array
		delete unsort;	
	}

	//clear up
	if(infile != &cin) delete infile;
	if(outfile != &cout) delete outfile;
	
	return;

}
