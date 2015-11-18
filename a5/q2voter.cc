#include "q2voter.h"
#include "q2printer.h"
#include "q2MPRNG.h"

Voter::Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer ) :
	id(id), printer(printer), voteTallier(voteTallier){

	}

void Voter::main() {
    // print start state
    printer.print(id, Voter::Start);

    // yield an random time
    yield(randomGen(19));

    // generate a ballot
    bool ballot = randomGen(1) == 1;
    //printer.print(id, Voter::Vote, ballot);

    // submit vote
    bool final = voteTallier.vote(id, ballot);

    // print finish state
    printer.print(id, Voter::Finished, final);
}