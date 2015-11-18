#include "q2producer.h"
#include "q2mprng.h"
void Producer::main(){
	for(int i=1; i<=p; i++){
	        //yield a random time
		yield(mprng(d));
                //insert a value into buffer
		b.insert(i);
	}
}
//constructor
Producer::Producer(BoundedBuffer<int> &buffer, const int Produce, const int Delay)
	: b(buffer), p(Produce), d(Delay){	
}
