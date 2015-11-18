#ifndef _BANK_H
#define _BANK_H

#include <vector>
#include <uC++.h>

_Monitor Bank {
	unsigned int numStudents;
	uCondition *courier;
	std::vector<unsigned int> studentaccount;
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif