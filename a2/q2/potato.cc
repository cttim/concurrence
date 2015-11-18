#include "potato.h"
#include <uC++.h>
#include <iostream>

using namespace std;

Potato::Potato(unsigned int maxTicks){
	max = maxTicks;
}

void Potato::reset(unsigned int maxTicks){
	numticks = rand() % maxTicks + 1;
	cout<<"  POTATO will go off after "<<numticks;
	if(numticks == 1){
		cout<<" toss"<<endl;
	}
	else{
		cout<<" tosses"<<endl;
	}
}

bool Potato::countdown(){
	numticks--;
	if(numticks > 0){
		return false;
	}
	else{
		return true;
	}
}
