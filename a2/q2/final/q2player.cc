#include "q2player.h"
#include "q2umpire.h"
#include "q2potato.h"
#include <uC++.h>
#include <iostream>

using namespace std;

void Player::main(){
	int next;						//the index of the next player
	while(!potato->countdown()){
		cout<<id<<" -> ";
		do{
			next = rand()% plist.size();		//choose the next player
		}while(plist[next]->getId() == id);
		plist[next]->toss(*potato);			//throw it to the next player
	}
	cout<<id<<" is eliminated"<<endl;
	umpire.set(id);						//reset the game

}

//constructor
Player::Player(Umpire &umpire, unsigned int Id, PlayerList &players):
	umpire(umpire),
	id(Id),
	plist(players)
{}

//throw the potato to the next player
void Player::toss(Potato &potato){
	Player::potato = &potato;
	resume();
}

//return the id of current player
unsigned int Player::getId(){
	return id;
}
