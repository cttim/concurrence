#ifndef PRINTER_H
#define PRINTER_H

_Monitor Printer{
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
private:
    unsigned int NumStudents;                  // number of students
    unsigned int NumVendingMachines;           // number of vending machines
    unsigned int NumCouriers;                  // number of couriers
    unsigned int TotalColumns;                        // total number of entites
    struct items{
        unsigned int num1;
        unsigned int num2;
        unsigned int id;
        char state;
        bool hasValue;
    };
    items* buffer;                                // stores current state
    void flush();                              // flushes and prints buffer
    unsigned int columnPosition( Kind kind, unsigned int lid );
    _Mutex void setUpBuffer(unsigned int id, char state, int value1, int value2 );

};

#endif