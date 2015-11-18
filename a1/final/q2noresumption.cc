#include <iostream>
#include <stdlib.h>
using namespace std;
/*
_Event H {                                               // uC++ exception type
  public:
    int &i;                                              // pointer to fixup variable at raise
    H( int &i ) : i( i ) {}
};
*/
class handler{
	public:
		int counter;
		handler(int x){
			counter = x;
		}
		void operator()(int x){counter = counter + x;}
		void fix(){
			if(counter == 0){
				cout<<"root ";
			}
			else{
				cout<<"f handler ";
				counter=counter-2;
			}
		}
};

void f( int &i, handler &h );
                                        // needed because handler is hoisted 
void f( int &i, handler &h) {
	cout << "f " << i << endl;
    	if ( rand() % 5 == 0 ){
		h.fix(); 
		cout<<i<<endl;
    	}               				// require correction ?
    	i -= 1;
    	if ( 0 < i ) {
		h(1);
		f( i,h );                             // recursion
	}	
}
int main(int argc, char** argv){
    handler life = handler(0);
    int times = 25, seed = getpid();
    switch ( argc ) {
      case 3: seed = atoi( argv[2] );                    // allow repeatable experiment
      case 2: times = atoi( argv[1] );                   // control recursion depth
      case 1: break;                                     // defaults
      default: cerr << "Usage: " << argv[0] << " times seed" << endl; exit( EXIT_FAILURE );
    }
    srand( seed );                                       // fixed or random seed
    f( times ,life);
}
