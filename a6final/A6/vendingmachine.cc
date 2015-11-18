#include "vendingmachine.h"
#include "nameserver.h"
#include "watcard.h"
#include "printer.h"
#include <iostream>
using namespace std;
//#include "WATCardOffice.h"

VendingMachine::VendingMachine(Printer &prt,NameServer &nameS,unsigned int id,unsigned int sodaCost, unsigned int maxStockPerFlavour)
    : printer(prt),
      nameServer(nameS),
      Id(id),
      SodaCost(sodaCost),
      MaxStockPerFlavour(maxStockPerFlavour) {
      	Instock=new unsigned int[NumFlavour];
      	for(unsigned int i=0;i<NumFlavour;i++){
      		Instock[i]=0;
      	}
      }

VendingMachine::~VendingMachine() {
	delete Instock;
}


void VendingMachine::buy( Flavours f, WATCard &card ){
	if(Instock[f]==0){
        uRendezvousAcceptor();
		_Throw Stock();
	}
	if(card.getBalance()<SodaCost){
        uRendezvousAcceptor();
		_Throw Funds();
	}
    printer.print(Printer::Vending, Id, 'B', f, Instock[f]);
	Instock[f]-=1;
	card.withdraw(SodaCost);
}

unsigned int* VendingMachine::inventory() {
  printer.print(Printer::Vending, Id, 'r');
  filling=true;
  return Instock;
}

void VendingMachine::restocked(){
	printer.print(Printer::Vending, Id, 'R');
	filling=false;
}

_Nomutex unsigned int VendingMachine::cost() {
  return SodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
  return Id;
}

void VendingMachine::main() {
    printer.print(Printer::Vending, Id, 'S', SodaCost);
    nameServer.VMregister(this);

  for (;;) {
  	_Accept(~VendingMachine) {
      break;
   } or _When(!filling)_Accept(buy){
   } or _Accept(inventory,restocked){

   }
  }
  //print finish
}







