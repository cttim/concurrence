#include "q2potato.h"
#include <uC++.h>
#include <iostream>

using namespace std;

Potato::Potato(unsigned int maxTicks){
	max = maxTicks;
}

void Potato::reset(unsigned int maxTicks){			//reset the ticks number
	numticks = rand() % maxTicks + 1;			//ticks num is between 1 to 10
	cout<<"  POTATO will go off after "<<numticks;
	if(numticks == 1){
		cout<<" toss"<<endl;
	}
	else{
		cout<<" tosses"<<endl;
	}
}

bool Potato::countdown(){
	numticks--;						//decrement the numticks
	if(numticks > 0){
		return false;
	}
	else{
		return true;
	}
}
