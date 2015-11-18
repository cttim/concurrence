#include <uC++.h>
#include <iostream>
#include <sstream>
#include "q2MPRNG.h"
#include "q2printer.h"
#include "q2voter.h"
#include "q2tallyVotes.h"

using namespace std;

MPRNG randomGen;

//usage function
void usage(char *argv[]){
	cerr<<"Usage: "<< argv[0]
		<< " Voters (>0 & V mod G = 0, default 6)"
		<< " Group (>0 & odd, defalut 3) Seed (> 0)"
		<<endl;
	exit(EXIT_FAILURE);
}

//convert char array into int
int convert(char *argv){
	int a;
	stringstream ss(argv);
	ss>>a;
	if(ss.fail()){
		return -1;
	}
	else{
		return a;
	}
}

const unsigned int VOTER = 6;
const unsigned int GROUP = 3;

void uMain::main(){
	//error checking
	if(argc > 4){
		usage(argv);
	}
	int voternum = VOTER;
	int groupnum = GROUP;
	int seed = getpid();
	//int tmp;
	if(argc >= 2){
		voternum = convert(argv[1]);
		if(voternum<=0){
			usage(argv);
		}
	}
	if(argc >= 3){
		groupnum = convert(argv[2]);
		if(groupnum<=0){
			usage(argv);
		}
		if(groupnum%2 == 0){
		        usage(argv);
		}
	}
	if(argc >= 4){
		seed = convert(argv[3]);
		if(seed<=0){
			usage(argv);
		}
		randomGen.seed(seed);
	}

	if(groupnum > voternum){
		usage(argv);
	}
	
	//create printer, tallvote and voter
	Printer printer(voternum);
	TallyVotes tallvotes(groupnum, printer);
	Voter *voter[voternum];

	//create the task
	for(int i=0; i<voternum; i++){
		voter[i] = new Voter(i, tallvotes, printer);
	}

	//clear up
	for(int j=0; j<voternum; j++){
		delete voter[j];
	}
}
