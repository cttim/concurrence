#include  "bank.h"

Bank::Bank(unsigned int numStudents) : numStudents(numStudents){
	for(unsigned int i=0; i<numStudents; i++){
		studentaccount.push_back(0);
	}

	courier = new uCondition[numStudents];
}

Bank::~Bank(){
	delete [] courier;
	studentaccount.clear();
}



void Bank::deposit(unsigned int id, unsigned int amount){
	studentaccount[id] += amount;

	if(!courier[id].empty()){
		courier[id].signal();
	}
}

void Bank::withdraw(unsigned int id, unsigned int amount){
	while(amount > studentaccount[id]){
		courier[id].wait();
	}

	studentaccount[id] -= amount;
}