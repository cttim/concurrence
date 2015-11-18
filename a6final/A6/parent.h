#ifndef _PARENT_H
#define _PARENT_H

#include "printer.h"
#include "bank.h"
#include "MPRNG.h"
#include <uC++.h>

//forward declare

_Monitor Printer;
_Monitor Bank;

_Task Parent {
	Printer &prt;
	Bank &bank;
	unsigned int parentalDelay;
	unsigned int numStudents;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
