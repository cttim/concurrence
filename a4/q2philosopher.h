#ifndef Q2PHILOSOPHER_H
#define Q2PHILOSOPHER_H
#include <uC++.h>
#include "q2table.h"

class Printer;
_Task Philosopher {
	unsigned id;
	Printer &printer;
	Table &table;
	void main();
  public:
    enum States { Thinking = 'T', Hungry = 'H', Eating ='E',
                   Waiting = 'W', Barging = 'B', Finished = 'F' };
    Philosopher( unsigned int id, unsigned int noodles, Table &table, Printer &prt );
};
#endif