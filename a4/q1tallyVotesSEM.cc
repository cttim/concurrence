#include "q1tallyVotes.h"
#include "q1Voter.h"
#include "q1printer.h"

//constructor
TallyVotes::TallyVotes( unsigned int group, Printer &printer ): groupnum(group), printer(printer){
	mutex = new uSemaphore(1);
	cond = new uSemaphore(0);
	barge = new uSemaphore(0);
	waitnum = 0;
	pic = 0;
	status = 0;
	bargeflag = false;
}

//vote func using semaphore
bool TallyVotes::vote(unsigned int id, bool ballot){
        // wait on mutex
	mutex->P();

	// if barging is not empty, wait on barging
	if(bargeflag){
		mutex->V();
		barge->P();
		mutex->P();
	}

	// release all threads from barging
	if(!barge->empty()){
		barge->V();
	}
	else{
		bargeflag = false;
	}

	// print the vote state
	printer.print(id, Voter::Vote, ballot);

	waitnum++;

	// collect the vote
	if(ballot){
		pic++;
	}
	else{
		status++;
	}

	// if waitnum is not enough, wait on condlock
	if(waitnum<groupnum){
	        // print the block state
		printer.print(id, Voter::Block, waitnum);
		mutex->V();
		cond->P();
		mutex->P();
		// print the unblock state
		printer.print(id, Voter::Unblock, groupnum-waitnum);
		waitnum--;
	}
	else{
	        // print the complete state
		printer.print(id, Voter::Complete);
		waitnum--;
		// get the result of voting
		result = pic>status;
		//reset pic and status
		pic = 0;
		status = 0;
	}

	// release other threads
	if(cond->empty()){
		if(!barge->empty()){
			barge->V();
		}
		else{
			bargeflag = false;
		}
	}
	else{
		bargeflag = true;
		cond->V();
	}
	
	//release mutex 
	mutex->V();
	return result;

}
