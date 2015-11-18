#ifndef Q1PRINTER_H
#define Q1PRINTER_H
#include <uC++.h>
#include "q1Voter.h"

_Monitor Printer {     // chose one of the two kinds of type constructor
  //a struct that contains the all the info of the voters
  struct voterstates{
  	bool full;
  	Voter::States state;
  	bool vote;
  	unsigned int numBlocked;
  };
  voterstates *voterstate;
  unsigned int voternum;
  //helper func flush and finish
  void flush();
  void finish(unsigned int id, bool vote);
  public:
    //constructor
    Printer( unsigned int voters );
    //destructor
    ~Printer();
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, bool vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};
#endif
