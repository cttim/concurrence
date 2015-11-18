#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"
#include <assert.h>

using namespace std;

// constructor of the this type of tallyvote
TallyVotes::TallyVotes(unsigned int group, Printer &printer) : printer(printer), group(group){
	waitnum = 0;
	pics = 0;
	status = 0;
}

// vote func
bool TallyVotes::vote(unsigned int id, bool ballot){
        // print the vote statement
	printer.print(id, Voter::Vote, ballot);

	waitnum++;

	// collect the vote
	if(ballot){
		pics++;
	}
	else{
		status++;
	}

	// if the arrival voters are not enough, the current voter need to wait
	if(waitnum<group){
	        // set the flag
		flag = false;

		// print the block statement
		printer.print(id, Voter::Block, waitnum);

		// call wait func
		WAITUNTIL(flag, , );

		waitnum--;

		// print unblock statement
		printer.print(id, Voter::Unblock, waitnum);
	}
	else{
	        // print complete statement
		printer.print(id, Voter::Complete);

		waitnum--;
		
		//get voting result
		decision = pics>status;
		
		// reset pics and status
		pics = 0;
		status = 0;

		// reset the flag
		flag = true;
	}

	// use return fucn
	RETURN(decision);
}
