#include <uC++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "q2boundedBuffer.h"
#include "q2consumer.h"
#include "q2producer.h"

using namespace std;

void usage(char *argv[]){
	cerr<<"Usage: "<<argv[0]<<" [ Cons (> 0) [ Prods (> 0) [ Produce (> 0) [ BufferSize (> 0) [ Delay (> 0) ] ] ] ] ]"<<endl;
}

//check whether the input string can be converted into an valid int
bool checkint(char *argv){
	char a = argv[0];
	if((a-'0')>9 || (a-'0')<0){
		return false;
	}
	return true;
}

//convert the string to int
int convert(char *argv){
	int a;
	stringstream ss(argv);
	ss>>a;
	if(ss.fail()){
		return -1;
	}
	else{
		return a;
	}
}
void uMain::main(){
	int cons = 5;
	int prods = 3;
	int produce = 10;
	int buffersize = 10;
	int delay = cons+prods;

	//parse command line and do error checking
	if(argc>=2){
		if(checkint(argv[1])){
			cons = convert(argv[1]);
			if(cons == -1){
				usage(argv);
				exit(EXIT_FAILURE);
			}
		}
		else{
			usage(argv);
			exit(EXIT_FAILURE);
		}
	}

	if(argc>=3){
		if(checkint(argv[2])){
			prods = convert(argv[2]);
			if(prods == -1){
				usage(argv);
				exit(EXIT_FAILURE);
			}
		}
		else{
			usage(argv);
			exit(EXIT_FAILURE);
		}
	}

	if(argc>=4){
		if(checkint(argv[3])){
			produce = convert(argv[3]);
			if(produce == -1){
				usage(argv);
				exit(EXIT_FAILURE);
			}
		}
		else{
			usage(argv);
			exit(EXIT_FAILURE);
		}
	}

	if(argc>=5){
		if(checkint(argv[4])){
			buffersize = convert(argv[4]);
			if(buffersize == -1){
				usage(argv);
				exit(EXIT_FAILURE);
			}
		}
		else{
			usage(argv);
			exit(EXIT_FAILURE);
		}
	}

	if(argc>=6){
		if(checkint(argv[5])){
			delay = convert(argv[5]);
			if(delay == -1){
				usage(argv);
				exit(EXIT_FAILURE);
			}
		}
		else{
			usage(argv);
			exit(EXIT_FAILURE);
		}
	}
	if(argc>6){
		usage(argv);
		exit(EXIT_FAILURE);
	}

#ifdef __U_MULTI__
	uProcessor pr[3] __attribute__((unused)); //create 3 kernel threads for a total of 4
#endif //__U_MULTI__

	//start
	//initialize the buffer
	BoundedBuffer<int> buffer(buffersize);

	//initialize the producer
	Producer *p[prods];
	for(int i=0; i<prods; i++){
		p[i] = new Producer(buffer, produce, delay);
	}

	//initialize the consumer
	Consumer *c[cons];
	//initialize an array to record each consumer's sum
	int consum[cons];
	//set sentinel to -1
	int sentinel = -1;
	for(int j=0; j<cons; j++){
		consum[j] = 0;
		c[j] = new Consumer(buffer, delay, sentinel, consum[j]);
	}

	//clear the producer
	for(int k=0; k<prods; k++){
		delete p[k];
	}

	//insert the sentinel value to let all the consumers quit
	for(int l=0; l<cons; l++){
		buffer.insert(sentinel);
	}

	//clear the consumers
	for(int m=0; m<cons; m++){
		delete c[m];
	}

	//caculate the sum
	int sum =0;

	for(int f=0; f<cons; f++){
		sum = sum + consum[f];
	}

	cout<<"total: "<<sum<<endl;

}












