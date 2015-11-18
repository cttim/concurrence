#ifndef _PLAYER
#define _PLAYER
#include "q2potato.h"
#include <vector>
using namespace std;

//forward declare
_Coroutine Umpire;

_Coroutine Player{
	Umpire &umpire;				//umpire, use reference since only one umpire exists
	unsigned int id;			//id of the player
	Potato *potato;				//potato
	void main();
	public:
		typedef vector<Player*> PlayerList;					//define the PlayerList
		Player(Umpire &umpire, unsigned int Id, PlayerList &players);
		unsigned int getId();							//return the id of the player
		void toss(Potato &potato);						//throw the potato
	private:		
		PlayerList &plist;
};
#endif
