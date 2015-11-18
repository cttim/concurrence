#ifndef Q1VOTER_H
#define Q1VOTER_H
#include <uC++.h>
#include "q1tallyVotes.h"

//forward declare
class Printer;
_Task Voter {
        //id of voter
	unsigned int id;
	//shared printer and tallyvote
	Printer &printer;
	TallyVotes &voteTallier;
	void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U',
                   Complete = 'C', Finished = 'F' };
    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer ); 
};
#endif


