#include "parent.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
	prt(prt), 
	bank(bank),
	parentalDelay(parentalDelay),
	numStudents(numStudents){ 
  //parentalDelay(parentalDelay){

}

void Parent::main(){
	unsigned int id;
	unsigned int amount;
	prt.print(Printer::Parent, 'S');
	while(true){
		_Accept(~Parent){
			break;
		}
		_Else{
			yield(parentalDelay);
			id = mprng(numStudents - 1);
			amount = mprng(1, 3);
			bank.deposit(id, amount);
			prt.print(Printer::Parent, 'D', id, amount);
		}
	}

	prt.print(Printer::Parent, 'F');

}
