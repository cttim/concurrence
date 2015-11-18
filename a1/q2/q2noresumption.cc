#include <iostream>
using namespace std;

_Event H {                                               // uC++ exception type
  public:
    int &i;                                              // pointer to fixup variable at raise
    H( int &i ) : i( i ) {}
};

class handler{
	public:
		int counter;
		handler(int x){
			//i = x;
			counter = x;
		}
		void operator()(int x){counter = counter + x;}
		void fix(){
			//counter--;
			if(counter == 0){
				cout<<"root ";
				//counter--;
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
    	//if ( rand() % 5 == 0 ) 
	if(i> 10 && i<20){
		h.fix(); 
		cout<<i<<endl;
		//cout<<"check error "<<h.counter<<endl;
    	}               				// require correction ?
    	//h(1);
	//cout<<"check error "<<h.counter<<endl;
    	i -= 1;
    	if ( 0 < i ) {
		h(1);
		f( i,h );                             // recursion
	}	
}
void uMain::main() {
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
