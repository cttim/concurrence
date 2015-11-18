#include <uC++.h>
#include "q2player.h"
#include "q2umpire.h"
#include "q2potato.h"
#include <iostream>

using namespace std;

//usage function 
void usage(char *argv[]){
 	cerr<<"Usage: "<<argv[0]<<" number-of-players (between 2 and 20) [ random-seed ]"<<endl;
  	exit(-1);
}

void uMain::main(){
	//set seed
  	int seed = getpid();
  	int num;
  	//error checking
	if(argc < 2 || argc > 3){
    		usage(argv);
  	}
	//get players num
  	num = atoi(argv[1]);

  	//error checking
  	if(num < 2 || num > 20){
    		usage(argv);
    		exit(-1);
  	}
  	if(argc == 3){
		//reset the seed
    		seed = atoi(argv[2]);
  	}

  	srand(seed);

	//create the playerlist
  	Player::PlayerList plist(num);
  
  	Umpire umpire(plist);
  
  	cout<<num<<" players in the match"<<endl;
  
  	for(int i=0; i<num; i++){
    		plist[i] = new Player(umpire, i, plist);
  	}
  
  	Player::PlayerList track(plist);

  	umpire.set(0);

	//clean up
  	for(int i=0; i<num; i++){
    		delete track[i];
  	}

}
