#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

#include <iostream>

using namespace std;

// constructor of this type of the tallyvote
TallyVotes::TallyVotes(unsigned int group, Printer &printer) : printer(printer), group(group){
	waitnum = 0;
	pics = 0;
	status = 0;
	currentid = -1;
}

// main func
void TallyVotes::main(){
        // infinity loop
	while(true){
	        // accept the destructor or vote func
		_Accept(~TallyVotes){
			break;
		}or _When(true) _Accept(vote){
		        // print the block statement
			printer.print(currentid, Voter::Block, waitnum);

			// if arrival voters are not enough, do nothing
			if(waitnum<group){

			}
			else{
			        // get the voting result
				decision = pics > status;

				// reset the pics and status
				pics = 0;
				status = 0;

				// print the complete statement
				printer.print(currentid, Voter::Complete);

				// use singalBlock to prevent barging
				tasklock.signalBlock();
			}
		}

	}

}

// vote func
bool TallyVotes::vote(unsigned int id, bool ballot){
        // reset the currentid, use to print
	currentid = id;

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

	// wait on tasklock
	tasklock.wait();

	// use singalBlock to prevent barging
	tasklock.signalBlock();

	waitnum--;

	// print the unblock statement
	printer.print(id, Voter::Unblock, waitnum);

	return decision;
}







