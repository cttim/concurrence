 #ifndef Q2PRINTER_H
#define Q2PRINTER_H
#include <uC++.h>
#include "q2philosopher.h"
 _Monitor Printer {            // choose one of the two kinds of type constructor
  struct Phstate{
  	bool full;
  	Philosopher::States state;
  	unsigned int bite;
  	unsigned int noodles;
  };
  Phstate *phstate;
  unsigned int nophil;
  void flush();
  void finish(unsigned int id);
  public:
    Printer( unsigned int NoOfPhil );
    void print( unsigned int id, Philosopher::States state );
    void print( unsigned int id, Philosopher::States state, unsigned int bite, unsigned int noodles );
};
#endif