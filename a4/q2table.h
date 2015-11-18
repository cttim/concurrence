#ifndef Q2TABLE_H
#define Q2TABLE_H

#include <uC++.h>
#include <uSemaphore>

class Printer;

#if defined( TABLETYPE_SEM )                // semaphore solution
// includes for this kind of table
class Table {
    // private declarations for this kind of table
#elif defined( TABLETYPE_INT )              // internal scheduling monitor solution
// includes for this kind of table
_Monitor Table {
    // private declarations for this kind of table
#elif defined( TABLETYPE_INTB )             // internal scheduling monitor solution with barging
// includes for this kind of table
_Monitor Table {
    // private declarations for this kind of table
    uCondition noforks;                     // only one condition variable (you may change the variable name)
    void wait();                            // barging version of wait
#else
    #error unsupported table
#endif
    // common declarations
  public:                                   // common interface
    Table( const unsigned int NoOfPhil, Printer &prt );
    void pickup( unsigned int id );
    void putdown( unsigned int id );
};

#endif