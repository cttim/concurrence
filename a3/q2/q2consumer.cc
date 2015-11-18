#include "q2consumer.h"
#include "q2mprng.h"
void Consumer:: main(){
        //yield a random time
	yield(mprng(d));
	//remove a num from buffer
	int num = b.remove();
	//keep removing the num from buffer until the num is equal to sentinel
	while(num != sen){
	        //sum the value it removed
		sum = sum + num;
		yield(mprng(d));
		num = b.remove();
	}
}

//constructor for consumer
Consumer::Consumer(BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum)
	: b(buffer), d(Delay), sen(Sentinel), sum(sum){
}

