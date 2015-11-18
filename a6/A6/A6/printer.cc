#include "printer.h"
#include <iostream>
using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ):
    NumStudents(numStudents), NumVendingMachines(numVendingMachines), NumCouriers(numCouriers) {

        //set up helpers
        TotalColumns = NumStudents + NumVendingMachines + NumCouriers + 5;
        buffer = new items[TotalColumns];
        for (unsigned int i = 0; i < TotalColumns; i++) {
            buffer[i].hasValues = false;
        }

        // Print header
        cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
        for (unsigned int i = 0; i < NumStudents; i++) {
            cout << "Stud" << i << '\t';
        }
        for (unsigned int i = 0; i < NumVendingMachines; i++) {
            cout << "Mach" << i << '\t';
        }
        for (unsigned int i = 0; i < NumCouriers; i++) {
            cout << "Cour" << i << '\t';
        }

        cout << endl;

        for (unsigned int i = 0; i < TotalColumns; i++) {
            cout << "=======" << '\t';
        }

        cout << endl;

    }

Printer::~Printer () {
    cout << "***********************" << endl;
    delete [] buffer;
}

void Printer::flush () {
    for (unsigned int i = 0; i < TotalColumns; i++) {
        if (buffer[i]) {
            cout << buffer[i].state;
            if (buffer[i].num1!= -1) {
                cout << buffer[i].value1;
                if (buffer[i].num2 != -1) {
                    cout << ',' << buffer[i].num2;
                }
            }
            buffer[i].hasValues = false;
        }
        cout << "\t";
    }
    cout << endl;
}

//implement public print functions using printMaster

void Printer::print( Kind kind, char state ) {

	unsigned int id = columnPosition(kind,0);
    if (state == 'F') {
       flush();
	   for ( unsigned int i = 0; i < total; i++) {
			if ( i == id) {
				cout<< state << "\t";
			} else {
				cout << "..." << "\t";
			} // if
		} // for
		cout << endl;
		return;
    }
    if (buffer[id].hasValues) 
        flush();
    setUpBuffer(id,state,-1,-1);


}


void Printer::print( Kind kind, char state, int value1 ) {
    unsigned int id = columnPosition(kind,0);
     if (buffer[id].hasValues) 
        flush();
    setUpBuffer(id,state,value1,-1);
}



void Printer::print( Kind kind, char state, int value1, int value2 ) {
    unsigned int id = columnPosition(kind,0);
     if (buffer[id].hasValues) 
        flush();
    setUpBuffer(id,state,value1,value2);
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
    unsigned int id = columnPosition(kind,lid);

    if (state == 'F') {

       flush();
	   for ( unsigned int i = 0; i < total; i++) {
			if ( i == id) {
				cout<< state << "\t";
			} else {
				cout << "..." << "\t";
			} // if
		} // for
		cout << endl;
		return;
    }
    if (buffer[id].hasValues) 
        flush();
    setUpBuffer(id,state,-1,-1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
   unsigned int id = columnPosition(kind,lid);
   if (buffer[id].hasValues) 
        flush();
    setUpBuffer(id,state,value1,-1);

}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
     unsigned int id = columnPosition(kind,lid);
     if (buffer[id].hasValues) 
        flush();
    setUpBuffer(id,state,value1,value2);


}

_Mutex void Printer::setUpBuffer(unsigned int id, char state, int value1, int value2 ){
    buffer[id].num1 = value1;
    buffer[id].num2 = value2;
    buffer[id].hasValues = true;
    buffer[id].state = state;
}

unsigned int Printer::columnPosition( Kind kind, unsigned int lid ) {
	// return position based on kind and id
	switch ( kind ) {
		case Student:
			return 5 + lid;
		case Vending:
			return 5 + NumStudents + lid;
		case Courier:
			return 5 + NumStudents + NumVendingMachines + lid;
		default:
			return (unsigned int) kind;
	} // switch
} //getPos















