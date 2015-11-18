#include "player.h"
#include "umpire.h"
#include "potato.h"
#include <uC++.h>
#include <iostream>

using namespace std;

void Player::main(){

	int next;	
	while(!potato->countdown()){
		cout<<id<<" -> ";
		do{
			next = rand()% plist.size();
		}while(plist[next]->getId() == id);
		plist[next]->toss(*potato);
	}
	cout<<id<<" is eliminated"<<endl;
	umpire.set(id);

}


Player::Player(Umpire &umpire, unsigned int Id, PlayerList &players):
	umpire(umpire),
	id(Id),
	plist(players)
{}

void Player::toss(Potato &potato){
	Player::potato = &potato;
	resume();
}

unsigned int Player::getId(){
	return id;
}
