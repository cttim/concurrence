#include "q1Voter.h"
#include "q1printer.h"
#include "q1MPRNG.h"

Voter::Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer ):
    	id(id), voteTallier(voteTallier), printer(printer){}

void Voter::main(){
	//print the start state
		printer.print(id, Voter:: Start);
		//yield a random time
		yield(randomGen(19));
		//generate random ballot (0 or 1)
		bool ballot = randomGen(1) == 1;
		//print vote state
		//printer.print(id, Voter:: Vote, ballot);
		//get the final result
		bool final = voteTallier.vote(id, ballot);
		//print finsh state
		printer.print(id, Voter:: Finished, final);
}

