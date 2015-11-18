#ifndef _TRUCK_H
#define _TRUCK_H
#include "MPRNG.h"
#include <uC++.h>

_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {

    void main();
    Printer& printer;
  	NameServer& nameServer;
  	BottlingPlant& Plant;
  	unsigned int NumVendingMachines;
  	unsigned int MaxStockPerFlavour;
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
};

#endif