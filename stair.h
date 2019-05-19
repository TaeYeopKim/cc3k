#ifndef _STAIR_H_
#define _STAIR_H_

#include "object.h"
#include "player.h"

class Stair: public Object {
	int floor;
	int chamb;
public:
	Stair(int newFloor, int newChamb);
	bool getAttacked(EnemyCharacter &whoFrom) override;
	bool getAttacked(PlayerCharacter &whoFrom) override;

	int getFloor();
	int getChamb();
};

#endif
