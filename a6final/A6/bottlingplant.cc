#include "bottlingplant.h"
#include "MPRNG.h"
#include "vendingmachine.h"
#include "truck.h"
#include <iostream>
#include "printer.h"
using namespace std;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameS, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ):
      printer(prt),
      nameServer(nameS),
      NumVendingMachines(numVendingMachines),
      MaxShippedPerFlavour(maxShippedPerFlavour),
      MaxStockPerFlavour(maxStockPerFlavour),
      TimeBetweenShipments(timeBetweenShipments),
      Shipment(new unsigned int[4]),
      ShutDown(false),
      picked(false) {
      	for(int i=0;i<4;i++){
      		Shipment[i]=0;
      	}
      }

BottlingPlant::~BottlingPlant() {
	delete truck;
	delete []Shipment;
}

void BottlingPlant::getShipment( unsigned int cargo[] ){
    if(ShutDown){
        uRendezvousAcceptor();
         _Throw Shutdown();
    }
    printer.print(Printer::BottlingPlant,'P');
	for (int i=0; i<4; i++) {
		cargo[i] = Shipment[i];
	}
	picked=true;
	//print 
}

void BottlingPlant::main() {
	printer.print(Printer::BottlingPlant, 'S');
    
    truck=new Truck(printer, nameServer, *this, NumVendingMachines, MaxStockPerFlavour);

	for(;;) {

		if (picked) {
			 int totalProduced = 0;
			for (int i=0; i<4; i++) {
				int temp = mprng(MaxShippedPerFlavour);
				Shipment[i] = temp;
				totalProduced += temp;
			}
			printer.print(Printer::BottlingPlant, 'G', totalProduced);
			picked = false;	
		}

		_Accept(~BottlingPlant) {
			ShutDown=true;
			break;
		} or _When(!picked) _Accept(getShipment) {
			yield(TimeBetweenShipments);
		}
	}
	//no outstanding calls, the acceptor is blocked until truck call getshipment
	_Accept(getShipment);
	
	printer.print(Printer::BottlingPlant, 'F');

}



