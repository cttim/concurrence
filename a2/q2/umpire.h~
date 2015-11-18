#ifndef _UMPIRE
#define _UMPIRE

#include "potato.h"
#include "player.h"
#include <vector>

_Coroutine Umpire{
	Player::PlayerList &plist;
	unsigned int eliminatedid;
	Potato potato;
	void main();
	public:
		Umpire(Player::PlayerList &players);
		void set(unsigned int player);
};

#endif
