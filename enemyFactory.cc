#include "enemyFactory.h"
#include <time.h>
#include <memory>
/*#include "human.h"
#include "elf.h"
#include "merchant.h"
#include "dwarf.h"
#include "orcs.h"
#include "halfling.h"*/

// temporary
#include "enemy.h"

using namespace std;

shared_ptr<EnemyCharacter> EnemyFactory::createEnemy() {
	srand(time(0));

	int randNum = rand() % 18;

	if (randNum >= 0 && randNum < 4) {
		return make_shared<Human>('H');
	} else if (randNum >= 4 && randNum < 7) {
		return make_shared<Dwarf>('W');
	} else if (randNum >= 7 && randNum < 12) {
		return make_shared<Halfling>('L');
	} else if (randNum >= 12 && randNum < 14) {
		return make_shared<Elf>('E');
	} else if (randNum >= 14 && randNum < 16) {
		return make_shared<Orc>('O');
	} else {
		return make_shared<Merchant>('M');;
	}
}

shared_ptr<EnemyCharacter> EnemyFactory::createEnemy(char race) {
	if (race == 'H') {
		return make_shared<Human>('H');
	} else if (race == 'W') {
		return make_shared<Dwarf>('W');
	} else if (race == 'L') {
		return make_shared<Halfling>('L');
	} else if (race == 'E') {
		return make_shared<Elf>('E');
	} else if (race == 'O') {
		return make_shared<Orc>('O');
	} else {
		return make_shared<Merchant>('M');;
	}
}

