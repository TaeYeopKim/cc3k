#include "stair.h"
#include "objecttype.h"
#include "object.h"

Stair::Stair(int newFloor, int newChamb): Object{'\\', ObjectType::Stair}, floor{newFloor}, chamb{newChamb} {}

bool Stair::getAttacked(EnemyCharacter &whoFrom) {
	return false;
}

bool Stair::getAttacked(PlayerCharacter &whoFrom) {
	return false;
}

int Stair::getFloor() {
	return floor;
}

int Stair::getChamb() {
	return chamb;
}
