#include <uC++.h>
#include "player.h"
#include "umpire.h"
#include "potato.h"
#include <iostream>

using namespace std;

void usage(char *argv[0]){
  cerr<<"Usage: "<<argv[0]<<" number-of-players (between 2 and 20) [ random-seed ]"<<endl;
  exit(-1);
}

void uMain::main(){
  int seed = getpid();
  int num;
  
  if(argc < 1 || argc > 3){
    usage(argv);
  }

  num = atoi(argv[1]);
  
  if(argc == 3){
    seed = atoi(argv[2]);
  }

  if(num < 2 || num > 20){
    usage(argv);
    exit(-1);
  }

  srand(seed);

  Player::PlayerList plist(num);
  
  Umpire umpire(plist);
  
  cout<<num<<" players in the match"<<endl;
  
  for(int i=0; i<num; i++){
    plist[i] = new Player(umpire, i, plist);
    // plist.push_back(p);
  }
  
  Player::PlayerList track(plist);

  umpire.set(0);

  for(int i=0; i<num; i++){
    delete track[i];
  }

}
