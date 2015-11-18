#include "student.h"


#include <iostream>
using namespace std;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases ):
	prt(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases){

}

void Student::main(){
	unsigned int bottlenum = mprng(1, maxPurchases);

	VendingMachine::Flavours favoriteflavor =  (VendingMachine::Flavours)mprng( 3 );

	prt.print( Printer::Student, id, 'S', favoriteflavor, bottlenum );

	VendingMachine *machine = NULL;

	WATCard::FWATCard futurecard = cardOffice.create(id, 5);

	WATCard *currentcard = NULL;

	while(bottlenum > 0){
		if(machine == NULL){
			machine = nameServer.getMachine(id);
			prt.print(Printer::Student, id, (char)SelectMachine, machine->getId());
		}

		yield(mprng(1, 10));

		try{
			currentcard = futurecard();
			machine->buy(favoriteflavor, *(futurecard()));

			prt.print(Printer::Student, id, 'B', currentcard->getBalance());
		        /*
			switch(status){
				//remember implement enum state
				case VendingMachine::BUY:
					bottlenum--;
					prt.print(Printer::Student, id, (char)BoughtSoda, currentcard->getBalance());
				break;

				case VendingMachine::STOCK:
					machine = NULL;
				break;

				case VendingMachine::FUNDS:
					//check machine->cost is right
					futurecard = cardOffice.transfer(id, machine->cost() + 5, currentcard);
				break;
				}*/
		} catch(WATCardOffice::Lost l){
			currentcard = NULL;
			futurecard = cardOffice.create(id, 5);
			prt.print(Printer::Student, id, (char)WATCardLost);
		} catch(VendingMachine::Funds f){
		        futurecard = cardOffice.transfer(id, machine->cost() + 5, currentcard);
		} catch(VendingMachine::Stock s){
		         machine = NULL;
		}
	}

	delete currentcard;
	prt.print(Printer::Student, id, (char)Printer::Finished);
}
