#include <iostream>
#include "q2printer.h"

using namespace std;

Printer::printer(unsigned int NoOfphil) : phstate(new Phstate[NoOfphil]){
	nophil = NoOfphil;

	for(int i=0; i<nophil; i++){
		phstate[i].full = false;
		cout<<"Phil"<<i<<'\t';
	}
	cout<<endl;

	for(int j=0; j<nophil; j++){
		cout<<"******"<<'\t';
	}
	cout<<endl;
}

Printer::~Printer(){
	delete [] phstate;
	cout<<"***********************"<<endl;
	cout<<"Philosophers terminated";
}

void Printer::printer(unsigned int id, Philosopher::States state){
	if(phstate[id].full){
		flush();
	}

	phstate[id].full = true;
	phstate[id].state = state;
}

void Printer::printer(unsigned int id, Philosopher::States state, unsigned int bite, unsigned int noodles){
	if(phstate[id].full){
		flush();
	}

	phstate[id].full = true;
	phstate[id].bite = bite;
	phstate[id].noodles = noodles;

}