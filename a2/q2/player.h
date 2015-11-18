#ifndef _PLAYER
#define _PLAYER
#include "potato.h"
#include <vector>
using namespace std;

_Coroutine Umpire;

_Coroutine Player{
	Umpire &umpire;
	unsigned int id;
	Potato *potato;
	void main();
	public:
		typedef vector<Player*> PlayerList;
		Player(Umpire &umpire, unsigned int Id, PlayerList &players);
		unsigned int getId();
		void toss(Potato &potato);
	private:		
		PlayerList &plist;
};
#endif
