#ifndef _TRUCK_H
#define _TRUCK_H
#include "MPRNG.h"
#include "vendingmachine.h"
#include <uC++.h>

_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {

  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
  private:
    void main();
    Printer& printer;
    NameServer& nameServer;
    BottlingPlant& Plant;
    unsigned int NumVendingMachines;
    unsigned int MaxStockPerFlavour;
    unsigned int* cargo;
    VendingMachine** machines;
};

#endif