#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include <vector>
#include <memory>

#include "view.h"
#include "cell.h"
#include "gold.h"
#include "enemy.h"
#include "potion.h"
#include "player.h"
#include "chamber.h"
#include "stair.h"

/*#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "human.h"
#include "merchant.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "dragon.h"
#include "halfling.h"
#include "boostAtk.h"
#include "woundAtk.h"
#include "boostDef.h"
#include "woundDef.h"
#include "restoreHealth.h"
#include "poisonHealth.h"
*/


class View;
class Object;
class EnemyCharacter;
class PlayerCharacter;
class Shade;
class Drow;
class Goblin;
class Troll;
class Vampire;

class Map {
	static size_t floor;

	std::vector<std::vector<std::vector<Cell>>> maps;
	std::vector<Chamber> chambers;
	std::vector<std::shared_ptr<EnemyCharacter>> enemies;
	std::vector<std::shared_ptr<Object>> items;
	std::shared_ptr<View> v;
	std::shared_ptr<PlayerCharacter> pc;
	std::shared_ptr<Stair> stair;
	size_t row;
	size_t col;
	bool f;
	int numChamber;
	char race;

	const int maxEnemies;
	const int maxPotion;
	const int maxGold;

	int curEnemies;
	int curPotion;
	int curGold;

	void createPotions(int numPotion);
	void createGolds(int numGold);
	void createEnemies(int numEnemies);
	void getChamber(Cell &curCell, char pcRace);

	void enemyTurn(); // need this?? don't need this??

	Coordinate getDirectedCoordinate(std::string dir);

public:
	Map(std::string fileName);

	void move(std::string dir);
	void attack(std::string dir);
	void drinkPotion(std::string dir);
	void init(char pcRace);

	void freeze();

	friend std::ostream &operator<<(std::ostream &out, const Map &m);

};

#endif

