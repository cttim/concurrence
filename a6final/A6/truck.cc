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
      MaxStockPerFlavour(maxStockPerFlavour),
      cargo(new unsigned int[4]),
      machines(nameS.getMachineList()){
        for (int i=0; i<4; i++) {
          cargo[i] = 0;
        }
}

Truck::~Truck(){
  delete [] cargo;
}

void Truck::main(){
  printer.print(Printer::Truck, 'S');
  for(;;){
    //coffee time

    yield(mprng(1,10));

    try{
      Plant.getShipment(cargo);
    }catch(BottlingPlant::Shutdown s){
      break;
    }
    unsigned int total;
    for(int i=0;i<4;i++){
      total += cargo[i];
    }
    printer.print(Printer::Truck, 'P', total);

     for (unsigned int i=0; i<NumVendingMachines && total > 0; i++) {
            printer.print(Printer::Truck, 'd', NumVendingMachines, total);

            unsigned int* inventory = machines[i]->inventory();

            unsigned int notfilled = 0;
            for (unsigned int f=0; f<4; f++) {
                unsigned int amount = min(MaxStockPerFlavour - inventory[f], cargo[f]);
                inventory[f] += amount;
                cargo[f] -= amount;
                total -= amount;
                notfilled += MaxStockPerFlavour - inventory[f];
            }
         
            // Indicate restock has completed
            machines[i]->restocked();
         
         if (notfilled > 0)
             printer.print(Printer::Truck, 'U', NumVendingMachines, notfilled);
         else
             printer.print(Printer::Truck, 'D', NumVendingMachines, total);
        }
    
       


  }
    printer.print(Printer::Truck, 'F');

}
