#ifndef _POTATO
#define _POTATO
class Potato {
	int max;				//maximun is 10
	int numticks; 				//num of ticks
	public:
		Potato( unsigned int maxTicks = 10 ); 
		void reset( unsigned int maxTicks = 10 ); 	//reset the potato and start the new game
		bool countdown();				//reduce the numticks
};
#endif
