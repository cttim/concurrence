#include "potato.h"
#include "player.h"
#include "umpire.h"
#include <iostream>

using namespace std;

void Umpire::main(){
	int set = 1;
	int next;
	while(plist.size() > 1){
		potato.reset();
		next = rand() % plist.size();
		cout<<"Set "<<set<<":"<<"\t"<<"U -> ";
		plist[next]->toss(potato);

		unsigned int counter = 0;
		for(counter = 0; counter < plist.size(); counter++){
			if(plist[counter]->getId() == eliminatedid){
				break;
			}
		}
		plist.erase(plist.begin() + counter);
		set++;
	}
	cout<<plist[0]->getId()<<" wins the Match!"<<endl;
}

Umpire::Umpire(Player::PlayerList &players):plist(players){
	//plist = players;
	eliminatedid = 20;
}

void Umpire::set(unsigned int id){
	eliminatedid = id;
	resume();
}
