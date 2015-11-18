#ifndef Q2PRODUCER_H
#define Q2PRODUCER_H
#include <uC++.h>
#include "q2boundedBuffer.h"

_Task Producer{
        BoundedBuffer<int> &b;                                //buffer
	const int p;                                          //produce num
	const int d;                                          //delay time
	void main();
public:
	//constructor
	Producer(BoundedBuffer<int> &buffer, const int Producer, const int Delay);
};
#endif
