#include <time.h>
#include "potionFactory.h"
/*#include "boostAtk.h"
#include "woundAtk.h"
#include "boostDef.h"
#include "woundDef.h"
#include "restoreHealth.h"
#include "poisonHealth.h"*/

// temporary
#include "potion.h"

using namespace std;

shared_ptr<Potion> PotionFactory::createPotion() {
	srand(time(0));

	int randNum = rand() % 6;

	if (randNum == 0) {
		return make_shared<BoostAtk>();
	} else if (randNum == 1) {
		return make_shared<WoundAtk>();
	} else if (randNum == 2) {
		return make_shared<BoostDef>();
	} else if (randNum == 3) {
		return make_shared<WoundDef>();
	} else if (randNum == 4) {
		return make_shared<RestoreHealth>();
	} else {
		return make_shared<PoisonHealth>();
	}
}

shared_ptr<Potion> PotionFactory::createPotion(char kind) {
	if (kind == '1') {
		return make_shared<BoostAtk>();
	} else if (kind == '4') {
		return make_shared<WoundAtk>();
	} else if (kind == '2') {
		return make_shared<BoostDef>();
	} else if (kind == '5') {
		return make_shared<WoundDef>();
	} else if (kind == '0') {
		return make_shared<RestoreHealth>();
	} else {
		return make_shared<PoisonHealth>();
	}
}

