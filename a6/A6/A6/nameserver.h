#ifndef NAMESERVER_H
#define NAMESERVER_H

#include <uC++.h>

class Printer;
_Task VendingMachine;


_Task NameServer {
    void main();
    Printer& printer;
  	unsigned int NumStudents;
  	unsigned int NumVendingMachines;
  	unsigned int SignedMachine;
 	VendingMachine** Machines;
  	unsigned int* MtoS;
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif