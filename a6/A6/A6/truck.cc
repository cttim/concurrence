#include "truck.h"
#include "bottlingplant.h"
#include "MPRNG.h"
#include "nameserver.h"
#include "printer.h"
#include "vendingmachine.h"

using namespace std;

Truck::Truck(Printer &prt,NameServer &nameS,BottlingPlant &plant,unsigned int numVendingMachines,unsigned int maxStockPerFlavour)
     :printer(prt),
      nameServer(nameS),
      Plant(plant),
      NumVendingMachines(numVendingMachines),
      cargo(new unsigned int[4]),
      MaxStockPerFlavour(maxStockPerFlavour) {
        for (int i=0; i<4; i++) {
          cargo[i] = 0;
        }
}

Truck::~Truck(){
  delete [] cargo;
  //Printer->print(Printer::Truck, 'F');
}

Truck::main(){
  //Printer->print(Printer::Truck, 'S');
  for(;;){
    //coffee time

    yield(mprng(1,10));

   /* try{
      Plant->getShipment(cargo);
    }catch(...){
      break;
    }*/
    unsigned int total;
    for(int i=0;i<4;i++){
      total += cargo[i];
    }
   // Printer->print(Printer::Truck, 'P', getTotalSodaIncargo());

     for (unsigned int i=0; i<numVendingMachines && total > 0; i++) {
            //Printer->print(Printer::Truck, 'd', vendingMachineCount, getTotalSodaInStock());

            // Begin restock for mth vending machine
            unsigned int* inventory = vendingMachines[i]->inventory();

            // Top up each flavour
            unsigned int notfilled = 0;
            for (unsigned int f=0; f<4; f++) {
                unsigned int amount = min(maxStockPerFlavour - inventory[f], cargo[f]);
                inventory[f] += amount;
                cargo[f] -= amount;
                total -= amount;
                notfilled += maxStockPerFlavour - inventory[f];
            }

            if (notfilled > 0)
             //Printer->print(Printer::Truck, 'U', vendingMachineCount, notfilled);
            else
             //Printer->print(Printer::Truck, 'D', vendingMachineCount, total);

            // Indicate restock has completed
            vendingMachines[m]->restocked();
        }


  }

}
