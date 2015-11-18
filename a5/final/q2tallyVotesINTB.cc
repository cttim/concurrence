#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

// constructor of this type of tallyvote
TallyVotes::TallyVotes(unsigned int group, Printer &printer) : printer(printer), group(group){
	waitnum = 0;
	pics = 0;
	status = 0;
	bargeflag = false;
}

// wait func
void TallyVotes::wait() {
    bench.wait();                              // wait until signalled
    while ( rand() % 5 == 0 ) {                // multiple bargers allowed
        _Accept( vote ) {                      // accept barging callers
        } _Else {                              // do not wait if no callers
        } // _Accept
    } // while
}

// signal func
void TallyVotes::signalAll() {                 // also useful
    while ( ! bench.empty() ) bench.signal();  // drain the condition
}

// vote func
bool TallyVotes::vote(unsigned int id, bool ballot){
        // if this is first voter reset the flag and signal the barging tasks
	if(waitnum == 0){
		bargeflag = false;
		if(!bench.empty()){
			signalAll();
		}
	}

	// if barging flag is set or waitnum is bigger than groupnum, the voter need to wait
	if(bargeflag || waitnum >= group){
		wait();
	}

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

	// if arrival voters are not enough, the current voter need to wait
	if(waitnum<group){
	        // print the block statement
		printer.print(id, Voter::Block, waitnum);

		// wait
		wait();
		waitnum--;

		// print the unblock statement
		printer.print(id, Voter::Unblock, waitnum);
	}
	else{
		printer.print(id, Voter::Complete);
		
		waitnum--;
		
		//get the voting reault
		decision = pics>status;
		
		//reset pics and status
		pics = 0;
		status = 0;
		
		//reset the barging flag and signal all the barging tasks
		bargeflag = true;
		signalAll();
	}

	return decision;
}
















