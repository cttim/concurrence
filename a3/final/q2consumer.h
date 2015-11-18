#ifndef Q2CONSUMER_H
#define Q2CONSUMER_H
#include <uC++.h>
#include "q2boundedBuffer.h"
_Task Consumer{
        BoundedBuffer<int> &b;                             //buffer
	const int d;                                       //delay time
	const int sen;                                     //sentinel value
	int &sum;                                          //sum of value it removed

	void main();

public:
        //constructor
	Consumer( BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum );
};
#endif
