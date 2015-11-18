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
        //print the vote statement
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

	//if the arrival voter is not enough, the current voter should wait
	if(waitnum<group){
	        //print block statement
		printer.print(id, Voter::Block, waitnum);
		//accept the next voter
		_Accept(vote);
		waitnum--;
		//print unblock statement
		printer.print(id, Voter::Unblock, waitnum);
	}
	else{
	        //print complete statement
		printer.print(id, Voter::Complete);
		waitnum--;
		//get the result
		decision = pics>status;

		//reset the pics and status
		pics = 0;
		status = 0;
	}

	return decision;
}
