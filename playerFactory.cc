#include <string>
#include "playerFactory.h"
//#include "shade.h"
//#include "drow.h"
//#include "vampire.h"
//#include "troll.h"
//#include "goblin.h"

// temporary
#include "player.h"

using namespace std;

shared_ptr<PlayerCharacter> PlayerFactory::createPlayer(char race) {
	if (race == 's') {
		return make_shared<Shade>();
	} else if (race == 'd') {
		return make_shared<Drow>();
	} else if (race == 'v') {
		return make_shared<Vampire>();
	} else if (race == 't') {
		return make_shared<Troll>();
	} else {
		return make_shared<Goblin>();;
	}
}

