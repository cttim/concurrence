#ifndef Q2VOTER_H
#define Q2VOTER_H

#include <uC++.h>
#include "q2tallyVotes.h"

//forward declare
class Printer;
_Task Voter {
	//id of the voter
	unsigned int id;
	//shared tallyvote and printer
	Printer &printer;
	TallyVotes &voteTallier;
	void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Barging = 'b',
                   Complete = 'C', Finished = 'F' };
    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer );
};
#endif