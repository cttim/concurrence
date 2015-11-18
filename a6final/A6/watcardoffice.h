#ifndef _WATCARDOFFICE_H
#define _WATCARDOFFICE_H

#include <uC++.h>
#include "watcard.h"
#include "printer.h"
#include "bank.h"

class Printer;
class Bank;

_Task WATCardOffice {
    struct Args{
        unsigned int sid;
        unsigned int amount;
        WATCard *card;

        Args(unsigned int sid, unsigned int amount, WATCard *card)
        : sid(sid), amount(amount), card(card){}
    };

    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;          // return future
        Job( Args args ) : args( args ){}
    };

    _Task Courier {     // communicates with bank
        void main();

        unsigned int id;

        WATCardOffice *office;

        Bank &bank;

        public:
            Courier(unsigned int id, WATCardOffice *office, Bank &bank);
    };                 

    void main();

    Printer &prt;
    Bank &bank;
    unsigned int numCouriers;
    Job *waitingjob;
    Courier **couriers;
    bool done;
  public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
