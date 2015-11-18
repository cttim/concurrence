#ifndef Q1TALLYVOTES_H
#define Q1TALLYVOTES_H

#include <uC++.h>
#include <uSemaphore.h>
#include <uBarrier.h>
class Printer;
#if defined( IMPLTYPE_MC )           // mutex/condition solution
// includes for this kind of vote-tallier
class TallyVotes {
    // private declarations for this kind of vote-tallier
	uCondLock barging;
	uCondLock condlock;
	uOwnerLock lock;
	bool bargeflag;
#elif defined( IMPLTYPE_SEM )        // semaphore solution
// includes for this kind of vote-tallier
class TallyVotes {
    uSemaphore *mutex;
    uSemaphore *cond;
    uSemaphore *barge;
    bool bargeflag;
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_BAR )        // barrier solution
// includes for this kind of vote-tallier
_Cormonitor TallyVotes : public uBarrier {
    // private declarations for this kind of vote-tallier
#else
    #error unsupported voter type
#endif
    // common declarations
    unsigned int groupnum;                           //max num of a group
    unsigned int waitnum;                            //num of waiting voters
    Printer &printer;
    unsigned int pic;                                //num of vote for pictures
    unsigned int status;                             //num of vote for status
    bool result;                                     //final decision
  public:                            // common interface
    TallyVotes( unsigned int group, Printer &printer );
    bool vote( unsigned int id, bool ballot );
    //destructor
    ~TallyVotes(){
        #if defined( IMPLTYPE_MC )           // mutex/condition solution

        #elif defined( IMPLTYPE_SEM )        // semaphore solution
        delete mutex;
        delete cond;
        delete barge;

        #elif defined( IMPLTYPE_BAR )        // barrier solution

        #endif

    }
};
#endif
