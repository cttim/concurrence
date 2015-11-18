#ifndef _STUDENT_H
#define _STUDENT_H

#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "vendingmachine.h"
#include "watcardoffice.h"
#include "watcard.h"
#include "MPRNG.h"
#include <uC++.h>

class printer;
class nameserver;
class watcardOffice;

_Task Student {
  Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	unsigned int id;
	unsigned int maxPurchases;
  void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );

    enum State{
    	SelectMachine = 'V', BoughtSoda = 'B', WATCardLost = 'L',
    };
};

#endif
