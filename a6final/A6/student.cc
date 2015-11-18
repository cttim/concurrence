#include "student.h"


#include <iostream>
using namespace std;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases ):
	prt(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases){

}

void Student::main(){
	unsigned int bottlenum = mprng(1, maxPurchases);

	VendingMachine::Flavours favoriteflavor =  (VendingMachine::Flavours)mprng(0, 3);

	prt.print( Printer::Student, id, 'S', favoriteflavor, bottlenum );

	VendingMachine *machine = NULL;

	WATCard::FWATCard futurecard = cardOffice.create(id, 5);

	WATCard *currentcard = NULL;

	while(bottlenum > 0){
		if(machine == NULL){
		//	cout<<"get here"<<endl;
			machine = nameServer.getMachine(id);
			//cout<<"get machine end"<<endl;
			prt.print(Printer::Student, id, (char)SelectMachine, machine->getId());
			//cout<<"machine id get"<<endl;
		}

		//cout<<"hahahahhhaha"<<endl;
		yield(mprng(1, 10));

		
		try{
			//cout<<"gggggggggggggggggggggggg"<<endl;			
			currentcard = futurecard();
			//cout<<"start to buy"<<endl;
			machine->buy(favoriteflavor, *(futurecard()));
			//cout<<"should print BUY"<<endl;
			prt.print(Printer::Student, id, 'B', currentcard->getBalance());
			bottlenum--;
			//cout<<"finished print buy"<<endl;
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
				//cout<<"no fund"<<endl;
		        futurecard = cardOffice.transfer(id, machine->cost() + 5, currentcard);
		} catch(VendingMachine::Stock s){
				//cout<<"out of stock"<<endl;
		        machine = NULL;
		        //cout<<"machine become null"<<endl;
		}
	}

	delete currentcard;
	prt.print(Printer::Student, id, 'F');
}
