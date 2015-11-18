#ifndef Q2TALLYVOTES_H
#define Q2TALLYVOTES_H

#include <uC++.h>
#include "AutomaticSignal.h"

class Printer;
#if defined( IMPLTYPE_EXT )                    // external scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_INT )                  // internal scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    uCondition intlock;
#elif defined( IMPLTYPE_INTB )                 // internal scheduling monitor solution with barging
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    uCondition bench;                          // only one condition variable (you may change the variable name)
    bool bargeflag;
    void wait();                               // barging version of wait
    void signalAll();                          // unblock all waiting tasks
#elif defined( IMPLTYPE_AUTO )                 // automatic-signal monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    AUTOMATIC_SIGNAL;
    bool flag;
#elif defined( IMPLTYPE_TASK )                 // internal/external scheduling task solution
_Task TallyVotes {
    // private declarations for this kind of vote-tallier
    uCondition tasklock;
    unsigned int currentid;
    //bool flag;
    void main();
#else
    #error unsupported voter type
#endif
    // common declarations
    Printer &printer;
    unsigned int group;
    unsigned int pics;
    unsigned int status;
    unsigned int waitnum;
    bool decision;
  public:                                     // common interface
    TallyVotes( unsigned int group, Printer &printer );
    bool vote( unsigned int id, bool ballot );
};
#endif
