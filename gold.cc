#include <iostream>
#include "gold.h"

Gold::Gold(size_t amount): Object{'G', ObjectType::Gold}, amount{amount} {}

bool Gold::getAttacked(EnemyCharacter &whoFrom) {
    return false;
}

bool Gold::getAttacked(PlayerCharacter &whoFrom) {
    return false;
}

size_t Gold::getGold() {
	return amount;
}


