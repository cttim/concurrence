#include "watcardoffice.h"
#include "MPRNG.h"

#include <iostream>
using namespace std;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
	: prt(prt), bank(bank), numCouriers(numCouriers), waitingjob(NULL), done(false){
		couriers = new Courier* [numCouriers];
		for(unsigned int i=0; i<numCouriers; i++){
			couriers[i] = new Courier(i, this, bank);
		}
	}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){
	WATCard *newcard = new WATCard();

	waitingjob = new Job(Args(sid, amount, newcard));

	prt.print(Printer::WATCardOffice, 'C', sid, amount);

	return waitingjob->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card){
	waitingjob = new Job(Args(sid, amount, card));

	prt.print(Printer::WATCardOffice, 'T', sid, amount);

	return waitingjob->result;
}

WATCardOffice::Job* WATCardOffice::requestWork(){
  //if(done) return NULL;
	Job *currentjob = waitingjob;
	waitingjob = NULL;
	return currentjob;
}

void WATCardOffice::main(){
	prt.print(Printer::WATCardOffice, 'S');

	while(true){
		_Accept(~WATCardOffice){
			done = true;
			for(unsigned int i =0; i<numCouriers; i++){
				_Accept(requestWork);
			}
			break;
		}
		or _When(waitingjob == NULL) _Accept(create, transfer);
		or _When(waitingjob != NULL)_Accept(requestWork){
			prt.print(Printer::WATCardOffice, 'W');
		}
	}

	for(unsigned int j =0; j<numCouriers; j++){
		delete couriers[j];
	}
	delete  [] couriers;
}

WATCardOffice::Courier::Courier(unsigned int id, WATCardOffice *office, Bank &bank)
	: id(id), office(office), bank(bank){

}

void WATCardOffice::Courier::main(){
	office->prt.print(Printer::Courier, id, 'S');

	while(true){
		Job *job = office->requestWork();

		if(job == NULL) break;

		if(mprng(5) == 1){
			job->result.exception(new Lost);

			delete job->args.card;
		}
		else{
			office->prt.print(Printer::Courier, id, 't', job->args.sid, job->args.amount);

			bank.withdraw(job->args.sid, job->args.amount);

			if(job->args.card == NULL) {
				job->args.card = new WATCard();
			}

			job->args.card->deposit(job->args.amount);

			office->prt.print(Printer::Courier, id, 'T', job->args.sid, job->args.amount);

			job->result.delivery(job->args.card);
		}

		delete job;
	}

	office->prt.print(Printer::Courier, id, 'F');

}
