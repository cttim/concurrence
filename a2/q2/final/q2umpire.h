#ifndef _UMPIRE
#define _UMPIRE

#include "q2potato.h"
#include "q2player.h"
#include <vector>

_Coroutine Umpire{
	Player::PlayerList &plist;					//plist is a vector of player
	unsigned int eliminatedid;					//id of player which need to be eliminated
	Potato potato;							//potato(only have one instance during one game)
	void main();
	public:
		Umpire(Player::PlayerList &players);			//costructor
		void set(unsigned int player);				//start the game
};

#endif
