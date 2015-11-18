#include "vendingmachine.h"

VendingMachine::VendingMachine(Printer &prt,NameServer &nameS,unsigned int id,unsigned int sodaCost, unsigned int maxStockPerFlavour)
    : printer(prt),
      nameServer(nameS),
      Id(id),
      SodaCost(sodaCost),
      MaxStockPerFlavour(maxStockPerFlavour) {
      	nameServer.VMRegister(this);
      	Instock=new unsigned int[NumFlavour];
      	for(unsigned int i=0;i<NumFlavour;i++){
      		Instock[i]=0;
      	}
      }

VendingMachine::~VendingMachine() {
	delete Instock;
}


void VendingMachine::buy( Flavours flavour, WATCard &card ){
	if(Instock[flavour]==0){
		//throw Stock;
	}
	if(card.getBalance()<SodaCost){
		//throw Funds;
	}
	Instock[flavour]-=1;
	card.withdraw(SodaCost);
	//print;
}

unsigned int* VendingMachine::inventory() {
  //print
  filling=true;
  return Instock;
}

void VendingMachine::restocked(){
	//print
	filling=false;
}

_Nomutex unsigned int VendingMachine::cost() {
  return SodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
  return Id;
}

void VendingMachine::main() {
 //print

  for (;;) {
  	_Accept(~VendingMachine) {
      break;
   } or _When(!filling)_Accept(buy){
   } or _Accept(inventory,restocked){

   }
  }
  //print finish
}







