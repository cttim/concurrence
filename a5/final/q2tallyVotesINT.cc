#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

//constructor of this type of tallyvote
TallyVotes::TallyVotes(unsigned int group, Printer &printer) : printer(printer), group(group){
	waitnum = 0;
	pics = 0;
	status = 0;
}

//vote func
bool TallyVotes::vote(unsigned int id, bool ballot){
        // print vote statement
	printer.print(id, Voter::Vote, ballot);

	//increment the arrival voter number
	waitnum++;

	//collect the vote
	if(ballot){
		pics++;
	}
	else{
		status++;
	}
	
	// if the arrival voters are not enough, the current voter need to wait
	if(waitnum<group){
	        // print the block statement
		printer.print(id, Voter::Block, waitnum);

		// wait on intlock
		intlock.wait();

		waitnum--;

		// print the unblock statement
		printer.print(id, Voter::Unblock, waitnum);

	}
	else{
	        // print the complete statement
		printer.print(id, Voter::Complete);

		waitnum--;

		//get the voting reault
		decision = pics>status;

		//reset the pics and status
		pics = 0;
		status = 0;

		//unblock the waiting voters
		for(unsigned int i=0; i<group; i++){
			intlock.signal();
		}
	}
	
	return decision;
}
