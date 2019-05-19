#ifndef _GOLD_H_
#define _GOLD_H_

#include "object.h"
#include "player.h"
#include "objecttype.h"

class Gold: public Object {
	size_t amount;
public:

	Gold(size_t amount);
	bool getAttacked(EnemyCharacter &whoFrom) override;
	bool getAttacked(PlayerCharacter &whoFrom) override;

	size_t getGold();
};

#endif
