#include "q1tallyVotes.h"
#include "q1Voter.h"
#include "q1printer.h"

//constructor of tallyvote
TallyVotes::TallyVotes( unsigned int group, Printer &printer ): groupnum(group), printer(printer){
	bargeflag = false;
	pic = 0;
	status = 0;
	waitnum = 0;
}

//vote func using mutual exclusion
bool TallyVotes::vote(unsigned int id, bool ballot){
	lock.acquire();

	//check the bargingglag
	if(bargeflag){
		barging.wait(lock);
	}

	//release all the threads in the barging lock
	if(!barging.empty()){
		barging.signal();
	}
	else{
		bargeflag = false;
	}

	//print the vote state
	printer.print(id, Voter:: Vote, ballot);

	waitnum++;

	//check the ballot
	if(ballot){
		pic++;
	}
	else{
		status++;
	}

	//if the waitnum is smaller than group, the voter has to wait
	if(waitnum<groupnum){
	        //print the block state
		printer.print(id, Voter::Block, waitnum);
		condlock.wait(lock);
		//print the unblock state	
		printer.print(id, Voter::Unblock, groupnum-waitnum);
		waitnum--;
	}
	else{
	        //print the complete state
		printer.print(id, Voter::Complete);
		waitnum--;
		//get result of the voting
		result = pic > status;
		pic = 0;
		status = 0;
	}
	
	//signal other voters
	if(condlock.empty()){
		if(!barging.empty()){
			barging.signal();
		}
		else{
			bargeflag = false;
		}
	}
	else{
		bargeflag = true;
		condlock.signal();
	}

	lock.release();
	return result;
	
}












