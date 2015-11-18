#ifndef AUTOMATICSIGNAL_H
#define AUTOMATICSIGNAL_H

#include <uC++.h>

#define AUTOMATIC_SIGNAL uCondition lock

#define WAITUNTIL(pred, before, after) \
	if(!(pred)){ \
		before; \
		lock.wait(); \
		after; \
	}

#define RETURN(expr...) \
	while(!lock.empty()){ \
		lock.signal(); \
	} \
	return (expr)

#endif
	