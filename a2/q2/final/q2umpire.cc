#include "q2potato.h"
#include "q2player.h"
#include "q2umpire.h"
#include <iostream>

using namespace std;

void Umpire::main(){
	//start the game
	int set = 1;
	int next;
	while(plist.size() > 1){
		//reset the potato and start a new round
		potato.reset();

		//choose a player to throw the potato
		next = rand() % plist.size();
		cout<<"Set "<<set<<":"<<"\t"<<"U -> ";
		plist[next]->toss(potato);

		unsigned int counter = 0;
		for(counter = 0; counter < plist.size(); counter++){
			if(plist[counter]->getId() == eliminatedid){
				break;
			}
		}
		//eliminate the loser
		plist.erase(plist.begin() + counter);
		set++;
	}
	cout<<plist[0]->getId()<<" wins the Match!"<<endl;
}

//constructor
Umpire::Umpire(Player::PlayerList &players):plist(players){	
	eliminatedid = 20;
}

//resume to start the game
void Umpire::set(unsigned int id){
	eliminatedid = id;
	resume();
}
