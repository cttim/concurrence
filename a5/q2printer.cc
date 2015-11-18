#include <iostream>
#include "q2printer.h"
using namespace std;

//the constructor
Printer::Printer(unsigned int voters):
	voterstate(new voterstates[voters]){
	voternum = voters;
	//print the format
	for(unsigned int i=0; i<voters; i++){
		voterstate[i].full = false;
		cout<<"Voter"<<i<<'\t';
	}
	cout<<endl;

	for(unsigned int j=0; j<voters; j++){
		cout<<"======= ";
	}
	cout<<endl;
}

//the destructor
Printer::~Printer(){
        //delete all voters
	delete [] voterstate;
	cout<<"====================="<<endl;
	cout<<"All tours statrted"<<endl;
}

//print func. use to handle state finish, statr.
void Printer::print(unsigned int id, Voter::States state){
	//check whether need to print
	if(voterstate[id].full){
		flush();
	}
	//update the voter state
	voterstate[id].full = true;
	voterstate[id].state = state;
}

//print func. use to handle state vote
void Printer::print(unsigned int id, Voter::States state, bool vote){
        //if state is finish, flush all the states and then call finish func
	if(state == Voter::Finished){
		flush();
		finish(id, vote);
		return;
	}

	//if the bit is dirty, you need to flush the states
	if(voterstate[id].full){
		flush();
	}
	//reset the dirty bit, state and vote
	voterstate[id].full = true;
	voterstate[id].state = state;
	voterstate[id].vote = vote;
}

//print func. use to handle states block and unblock
void Printer::print(unsigned int id, Voter::States state, unsigned int numBlocked){
        // if the bit is dirty, flush all the state
	if(voterstate[id].full){
		flush();
	}

	// reset the dirty bit, state and numblocks
	voterstate[id].full = true;
	voterstate[id].state = state;
	voterstate[id].numBlocked = numBlocked;
}

//helper func finish. print the state for the finished voter
void Printer::finish(unsigned int id, bool vote){
	for(unsigned int i=0; i<voternum; i++){
		if(i == id){
			cout<<"F "<<vote;
		}
		else{
			cout<<"... ";
		}
		cout<<'\t';
	}
	cout<<endl;
}

//helper func flush. print the states of all voters
void Printer::flush(){
	for(unsigned int i=0; i<voternum; i++){
	        // if the bit is dirty, need to print the state of the voter
		if(voterstate[i].full){
			Voter::States tmpstate = voterstate[i].state;
			//cast the state and print 
			cout<<(char)tmpstate;
			if(tmpstate == Voter::Vote){
				cout<<' '<<voterstate[i].vote;
			}
			else if(tmpstate == Voter::Block){
				cout<<' '<<voterstate[i].numBlocked;
			}
			else if(tmpstate == Voter::Unblock){
				cout<<' '<<voterstate[i].numBlocked;
			}
			else{

			}
		}
		cout<<'\t';
		//reset the dirty bit
		voterstate[i].full = false;
	}
	cout<<endl;
}

















