#ifndef BottlingPlant_H
#define BottlingPlant_H
#include <uC++.h>
#include "truck.h"

class Printer;
_Task NameServer;

_Task BottlingPlant {
    void main();
    Printer& printer;
  	NameServer& nameServer;
  	unsigned int NumVendingMachines;
  	unsigned int MaxShippedPerFlavour;
    unsigned int MaxStockPerFlavour;
    unsigned int TimeBetweenShipments;
  	unsigned int* Shipment;
  	Truck* truck;
  	bool ShutDown;
  	bool picked;
  public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[] );
};

#endif