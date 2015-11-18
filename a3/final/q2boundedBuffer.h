#ifndef Q1_BOUNDEDBUFFER_H
#define Q1_BOUNDEDBUFFER_H
#include <uC++.h>
#include <assert.h>
#include <list>
using namespace std;

//buffer class
template<typename T> class BoundedBuffer {
  public:
    BoundedBuffer( const unsigned int size = 10 );                          //constructo
    ~BoundedBuffer();                                                       //destructor
    void insert( T elem );                                                  //insert value into buffer
    T remove();                                                             //remove one value from buffer
private:
        const unsigned int max;                                             //max size of buffer
	unsigned int head;                                                  //head of the buffer. indicate which value should be removed next time
	unsigned int size;                                                  //num of elem in the buffer
	T *buffer;                                                          //buffer array
	uOwnerLock lock;                                                    //lock
	uCondLock pro;                                                      //condition lock
	uCondLock cons;
#ifdef NOBUSY
	uCondLock barge;                                                    //nobusy wait need an extra condition lock
	bool bargeflag;                                                     //barging flag
#endif
	bool full();                                                        //check whether the buffer is full

	bool empty();                                                       //check whether the buffer is empty

	void add(T elem);                                                   //add one elem to buffer

	T out();                                                            //remove one elem from buffer


};

#ifdef BUSY
//constructor of buffer
template<typename T>
BoundedBuffer<T>:: BoundedBuffer(const unsigned int size): max(size){
	buffer = new T[size];
	head = 0;
	BoundedBuffer::size = 0;
}

//insert an elem to buffer
template<typename T>
void BoundedBuffer<T>::insert(T elem){
        //get ownerlock
	lock.acquire();
	while(full()){
	        //sleep the thread and release the ownerlock
		pro.wait(lock);
	}
        //insert elem to the buffer
	add(elem);
        //signal the consumer thread
	cons.signal();
	//release the ownerlock
	lock.release();
} 

//remove an elem from buffer 
template<typename T>
T BoundedBuffer<T>:: remove(){
        //get ownerlock
	lock.acquire();
	while(empty()){
	        //sleep the thread and relase the ownerlock
		cons.wait(lock);
	}
        //remove the elem from buffer
	T result = out();
	//signal the producer thread
	pro.signal();
	//release the ownerlock
	lock.release();
	return result;
}
#endif

#ifdef NOBUSY
//constructor
template<typename T>
BoundedBuffer<T>::BoundedBuffer(const unsigned int size):max(size){
	buffer = new T[size];
	head = 0;
	BoundedBuffer::size = 0;
	bargeflag = false;                                                //set the barging flag to false in the beginning
}

//insert one elem to the buffer
template<typename T>
void BoundedBuffer<T>:: insert(T elem){
        //get ownerlock
	lock.acquire();
	//check the barging flag.
	if(bargeflag){
		barge.wait(lock);
	}
	//check whether the buffer is full
	if(full()){
		if(!barge.empty()){
		        //if the barging condlock is not empty, signal it 
			barge.signal();
		}
		else{
		        //reset the barging flag
			bargeflag = false;
		}
		pro.wait(lock);
	}

	//insert the elem
	add(elem);

	//check if consumer condlock is empty
	if(cons.empty()){
		if(!barge.empty()){
		        //if consumer condlock is empty and barging condlock is not, signal barging condlock
			barge.signal();
		}
		else{
		        //reset the flag
			bargeflag = false;
		}
	}
	else{
	        //set the barging flag to true before signal
		bargeflag = true;
		cons.signal();
	}
	//release the lock
	lock.release();
}

//remove one elem from buffer
template<typename T>
T BoundedBuffer<T>:: remove(){
        //get ownerlock
	lock.acquire();
	//check the barging flag
	if(bargeflag){
		barge.wait(lock);
	}

	if(empty()){
		if(!barge.empty()){
		        //when buffer is empty and barging condlock is not empty, signal it
			barge.signal();
		}
		else{
		        //reset the flag
			bargeflag = false;
		}
		cons.wait(lock);
	}

	//pop one elem from buffer
	T result = out();

	if(pro.empty()){
		if(!barge.empty()){
		        //if producer condlock is empty and barging condlock is not, signal the barging condlock
			barge.signal();
		}
		else{
		        //reset the flag
			bargeflag = false;
		}
	}
	else{
	        //set the flag to false before signal
		bargeflag = true;
		pro.signal();
	}

	//release the ownerlock
	lock.release();

	return result;

}

#endif

//destructor
template<typename T>
BoundedBuffer<T>:: ~BoundedBuffer(){
	delete [] buffer;
}

//return true if buffer is full, otherwise false
template<typename T>
bool BoundedBuffer<T>:: full(){
	if(size == max){
		return true;
	}
	else{
		return false;
	}
}

//return true if buffer is empty, otherwise false
template<typename T>
bool BoundedBuffer<T>:: empty(){
	if(size == 0){
		return true;
	}
	else{
		return false;
	}
}

//add one elem to buffer
template<typename T>
void BoundedBuffer<T>::add(T elem){
        //assert the buffer is not full
	assert(!full());
	//update the head and size
	buffer[(head+size)%max] = elem;
	size++;
}

//remove one elem from buffer
template<typename T>
T BoundedBuffer<T>::out(){
        //assert the buffer is not empty
	assert(!empty());
	T tmp = buffer[head];
	//update the head and size
	head = (head+1)%max;
	size--;
	return tmp;
}

#endif
