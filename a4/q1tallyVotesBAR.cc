#include "q1tallyVotes.h"
#include "q1Voter.h"
#include "q1printer.h"

//constructor
TallyVotes::TallyVotes(unsigned int group, Printer &printer): uBarrier(group), groupnum(group), printer(printer){
  waitnum = 0;
  pic = 0;
  status = 0;
}

//vote func using ubarrier
bool TallyVotes::vote(unsigned int id, bool ballot){
  waitnum++;

  //collect the vote
  if(ballot){
    pic++;
  }
  else{
    status++;
  }

  //print the vote state
  printer.print(id, Voter::Vote, ballot);

  // if the waitnum is not enough, block the thread
  if(waitnum < groupnum){
    printer.print(id, Voter::Block, waitnum);

    uBarrier::block();

    printer.print(id, Voter::Unblock, waitnum);
  
    waitnum--;
  }
  else{
    //print the complete state
    printer.print(id, Voter::Complete);

    //release other block threads
    uBarrier::block();

    //get the result of voting
    result = pic > status;

    //reset the pic and status
    pic = 0;

    status = 0;

    waitnum--;
  }
  return result;
}
