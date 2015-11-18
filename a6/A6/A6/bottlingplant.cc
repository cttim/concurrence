#include "bottlingplant.h"
#include "MPRNG.h"
#include "vendingmachine.h"
#include "truck.h"
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
      truck(new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour)),
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
	if(ShutDown)
		//throw (new Shutdown);
	for (int i=0; i<4; i++) {
		cargo[i] = Shipment[i];
	}
	picked=true;
	//print 
}

void BottlingPlant::main() {
	//printer->print(Printer::BottlingPlant, 'S');

	for(;;) {

		if (picked) {
			//int bottlesProduced = 0;
			for (int i=0; i<4; i++) {
				//int bottles = rng(MaxShippedPerFlavour);
				Shipment[i] = mprng(MaxShippedPerFlavour);
				//bottlesProduced += bottles;
			}
			//printer->print(Printer::BottlingPlant, 'G', bottlesProduced);
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
	
	//printer->print(Printer::BottlingPlant, 'F');

}



