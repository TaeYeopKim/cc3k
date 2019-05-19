#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <memory>
#include "map.h"
#include "playerFactory.h"
#include "potionFactory.h"
#include "enemyFactory.h"
#include "goldFactory.h"
#include "cellCorFactory.h"
#include "coordinate.h"
#include "objecttype.h"

using namespace std;

size_t Map::floor = -1;

Map::Map(string fileName): v{make_shared<View>(fileName)}, pc{nullptr}, row{0}, col{0}, f{false}, numChamber{0},
maxEnemies{20}, maxPotion{10}, maxGold{10}, curEnemies{0}, curPotion{0}, curGold{0} {
	ifstream file(fileName);
	string line;

	int tmpRow = 0;
	int count = 0;
	int floorCount = 0;
	while (floorCount < 5) {
		getline(file, line);
		col = line.length();
		if (line[0] == '|' && line[1] == '-' && count % 2 == 1) {

			int i = 0;
			vector<Cell> cellVec;
			maps.at(floorCount).emplace_back(cellVec);
			for (char &c: line) {
				bool isWall = (c == ' ' || c == '|' || c == '-' || c == '+') ? true : false;
				bool isEnemyPath = (c == '.') ? true : false;
				maps.at(floorCount).back().emplace_back(Cell{ c, isWall, Coordinate{i, (int)tmpRow}, isEnemyPath});
				i++;
			}
			tmpRow++;

			count++;
			floorCount++;
			row = tmpRow;
			tmpRow = 0;
		} else if (line[0] == '|' && line[1] == '-' && count % 2 == 0) {
			vector<vector<Cell>> vec;
			maps.emplace_back(vec);

			int i = 0;
			vector<Cell> cellVec;
			maps.at(floorCount).emplace_back(cellVec);
			for (char &c: line) {
				bool isEnemyPath = (c == '.') ? true : false;
				maps.at(floorCount).back().emplace_back(Cell{ c, true, Coordinate{i, (int)tmpRow}, isEnemyPath});
				//maps.at(floorCount).back().emplace_back(Cell{ c, true, Coordinate{i, (int)tmpRow}});
				i++;
			}
			tmpRow++;
		} else {
			int i = 0;
			vector<Cell> cellVec;
			maps.at(floorCount).emplace_back(cellVec);
			for (char &c: line) {
				bool isWall = (c == ' ' || c == '|' || c == '-' ) ? true : false;
				bool isEnemyPath = (c == '.') ? true : false;
				maps.at(floorCount).back().emplace_back(Cell{ c, isWall, Coordinate{i, (int)tmpRow}, isEnemyPath});
				i++;
			}
			tmpRow++;
			count++;
		}
	}

	file.close();
}

void Map::createPotions(int numPotion) {
	PotionFactory pf;
	CellCorFactory ccf;

	for (int i = 0; i < numPotion; i++) {
		shared_ptr<Potion> potion = pf.createPotion();
		items.emplace_back(potion);
		while (true) {
			int chamberNum = ccf.getChamberNum(numChamber);
			Coordinate cellCor = ccf.getCoordinate(chambers.at(chamberNum));
			Cell &theCell = maps.at(floor).at(cellCor.y).at(cellCor.x);
			if (!theCell.getFilled()) {
				theCell.setObject(potion);
				v->notify(*potion);
				break;
			}
		}
	}
}

void Map::createGolds(int numGold) {
	GoldFactory gf;
	CellCorFactory ccf;

	for (int i = 0; i < numGold; i++) {
		shared_ptr<Gold> gold = gf.createGold();
		items.emplace_back(gold);
		while (true) {
			int chamberNum = ccf.getChamberNum(numChamber);
			Coordinate cellCor = ccf.getCoordinate(chambers.at(chamberNum));
			Cell &theCell = maps.at(floor).at(cellCor.y).at(cellCor.x);
			if (!theCell.getFilled()) {
				theCell.setObject(gold);
				v->notify(*gold);
				break;
			}
		}
	}
}

void Map::createEnemies(int numEnemies) {
	EnemyFactory ef;
	CellCorFactory ccf;

	for (int i = 0; i < numEnemies; i++) {
		shared_ptr<EnemyCharacter> enemy = ef.createEnemy();
		enemies.emplace_back(enemy);
		while (true) {
			int chamberNum = ccf.getChamberNum(numChamber);

			Coordinate cellCor = ccf.getCoordinate(chambers.at(chamberNum));
			Cell &theCell = maps.at(floor).at(cellCor.y).at(cellCor.x);

			if (!theCell.getFilled()) {
				theCell.setObject(enemy);
				v->notify(*enemy);
				break;
			}
		}
	}
}

Coordinate Map::getDirectedCoordinate(string dir) {
	Coordinate curCor = pc->getCurCoordinate();

	if (dir == "no") curCor.y--;
	else if (dir == "so") curCor.y++;
	else if (dir == "we") curCor.x--;
	else if (dir == "ea") curCor.x++;
	else if (dir == "nw") {
		curCor.y--;
		curCor.x--;
	}
	else if (dir == "ne") {
		curCor.y--;
		curCor.x++;
	}
	else if (dir == "sw") {
		curCor.y++;
		curCor.x--;
	}
	else {
		curCor.y++;
		curCor.x++;
	}

	return curCor;
}

void Map::move(string dir) {
	Coordinate curCor = getDirectedCoordinate(dir);
	Cell &toCell = maps.at(floor).at(curCor.y).at(curCor.x);

	shared_ptr<Object> targetObj = toCell.getObject();

	if (targetObj && targetObj->type == ObjectType::Stair) {
		if (floor == 4) {
			cout << endl;
			cout << "Congratulations! Your adventure has finished!!" << endl;
			cout << "Press r to restart." << endl;
			cout << "Press q to quit." << endl;
		} else {
			cout << "Loading next floor..." << endl;
			cout << endl;

			v->goUpAFloor();
			init(race);
		}
	}

	if (!targetObj && !toCell.getIsWall()) { // move to the empty cell
		Coordinate oldCor = pc->getCurCoordinate();
		Cell &fromCell = maps.at(floor).at(oldCor.y).at(oldCor.x);
		fromCell.setObject(nullptr);
		toCell.setObject(pc);
		pc->move(curCor);
		v->notify(*pc);
	} else if (targetObj && targetObj->type == ObjectType::Gold) { // move to the cell, and pickup gold
		std::shared_ptr<Gold> gold = std::dynamic_pointer_cast<Gold> (targetObj);
		pc->consume(*gold);
		Coordinate oldCor = pc->getCurCoordinate();
		Cell &fromCell = maps.at(floor).at(oldCor.y).at(oldCor.x);
		fromCell.setObject(nullptr);
		toCell.setObject(pc);
		pc->move(curCor);
		v->notify(*pc);
	}

	// --- TEMP ------------------------------------------------------
	// move message
	Coordinate oldCor = pc->getOldCoordinate();
	std::cout << "PC moves ";
	string outDir;
	if (dir == "no") outDir = "North";
	else if (dir == "so") outDir = "South";
	else if (dir == "ne") outDir = "North-East";
	else if (dir == "nw") outDir = "North-West";
	else if (dir == "se") outDir = "South-East";
	else if (dir == "sw") outDir = "South-West";
	else if (dir == "ea") outDir = "East";
	else if (dir == "we") outDir = "West";	
	std::cout << outDir;
	// potion recognition
	int c = 0;
	int unknownCount = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i == 0 && j == 0) continue;
			Cell &neighbor = maps.at(floor).at(curCor.y + i).at(curCor.x + j);
			std::shared_ptr<Object> neighborObj = neighbor.getObject();			
			if (neighborObj && neighborObj->type == ObjectType::Potion) {
				std::shared_ptr<Potion> pot = std::dynamic_pointer_cast<Potion> (neighborObj);
				if (pc->doesKnow(*pot)) {						
					if (c != 0) std::cout << ", ";
					else std::cout << " and see a ";
					++c;
					string strPot;
					switch (pot->potionType)
					{
						case PotionType::BoostAtk:
						strPot = "BA";
						break;
						case PotionType::BoostDef:
						strPot = "BD";
						break;
						case PotionType::WoundAtk:
						strPot = "WA";
						break;
						case PotionType::WoundDef:
						strPot = "WD";
						break;
						case PotionType::RestoreHealth:
						strPot = "RH";
						break;
						case PotionType::PoisonHealth:
						strPot = "PH";
						break;
						default:
						break;
					}	
					std::cout << strPot;
				}
				else ++unknownCount;
			}
		}
	}
	if (unknownCount > 0) std::cout << " and see " << (unknownCount == 1 ? "an unknown potion" : (std::to_string(unknownCount) + " unknown potions"));

	std::cout << "." << endl;
	// --- end pot recognition message ---------
	// --- TEMP ------------------------------------------------------
	
	enemyTurn();
}

////////// not done
void Map::enemyTurn() {
	if (f) return;

	// enemy turn;
	
	for (auto &enemy: enemies) {

		// if player is around attack
		bool playerAround = false;
		Coordinate enemyCoor = enemy->getCurCoordinate();
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (maps.at(floor).at(enemyCoor.y-j).at(enemyCoor.x-i).getObject() &&
				maps.at(floor).at(enemyCoor.y-j).at(enemyCoor.x-i).getObject()->getSymb() == '@') {	// or enemy.getSym()?
					playerAround = true;
				bool shouldBeDestroyed = pc->getAttacked(*enemy);
				if (shouldBeDestroyed) {
					maps.at(floor).at(enemyCoor.y-j).at(enemyCoor.x-i).setObject(nullptr);
					maps.at(floor).at(enemyCoor.y-j).at(enemyCoor.x-i).setSymbol('.');
						pc->setDead(); //set the symbol of player character o '.'
						v->notify(*pc);
					}
				}
			}
		}

		// player is not around the enemy character
		// print out the enemy action
		if (!playerAround) {
			vector<Coordinate> surroundings;
			int numSurr = 0;
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					Cell curCell = maps.at(floor).at(enemyCoor.y-j).at(enemyCoor.x-i);
					if ((curCell.getObject() == nullptr) && (curCell.getIsEnemyPath())) {
						++ numSurr;
						surroundings.emplace_back(curCell.getCor());
					}
				}
			}
			srand(time(0));  
			int random = rand()%numSurr;
			Coordinate enemyNextMoveCoor = surroundings.at(random);

			Cell &toCell = maps.at(floor).at(enemyNextMoveCoor.y).at(enemyNextMoveCoor.x);
			Coordinate oldCor = enemy->getCurCoordinate();
			Cell &fromCell = maps.at(floor).at(oldCor.y).at(oldCor.x);
			fromCell.setObject(nullptr);
			fromCell.setSymbol('.');
			toCell.setObject(enemy);
			v->notify(*enemy);
			
		}
	}
	// merchant only attacks if static bool isHostile is true
	// print out the enemy action
}

//////// not done
void Map::attack(string dir) {
	Coordinate cur = getDirectedCoordinate(dir);
	shared_ptr<Object> targetObj = maps.at(floor).at(cur.y).at(cur.x).getObject();

	// Player attack Enemy
	// added feature attack information print in player.cc/attack
	if (targetObj) {
		bool shouldBeDestroyed = targetObj->getAttacked(*pc);
		if (shouldBeDestroyed) {
			// targetObj->setIsDead();
			Coordinate enemyCoor = targetObj->getCurCoordinate();
			maps.at(floor).at(enemyCoor.y).at(enemyCoor.x).setObject(nullptr);
			maps.at(floor).at(enemyCoor.y).at(enemyCoor.x).setSymbol('.');
			targetObj->setDead(); // set the symbol to '.' object*
			v->notify(*targetObj);
		}
	}
	
	enemyTurn();
}

void Map::drinkPotion(string dir) {
	Coordinate curCor = getDirectedCoordinate(dir);

	Cell &toCell = maps.at(floor).at(curCor.y).at(curCor.x);
	shared_ptr<Object> targetObj = toCell.getObject();

	if (targetObj && targetObj->type == ObjectType::Potion) {
		std::shared_ptr<Potion> pot = std::dynamic_pointer_cast<Potion> (targetObj);
		pc->consume(*pot);
		toCell.setObject(nullptr);
		v->notify(*pot);
	}

	enemyTurn();
}

void Map::getChamber(Cell &curCell, char pcRace) {
	if (curCell.getCounted() || curCell.getIsWall()) return;
	char sym = curCell.getSymbol();
	Coordinate cor = curCell.getCor();
	if (sym != ' ' && sym != '#' && sym != '-' && sym != '|' && sym != '+') {
		curCell.setCounted();
		if (sym == '\\') {
			stair = make_shared<Stair>(floor, numChamber - 1);
			curCell.setObject(stair);
			v->notify(*stair);
		}
		else if (sym == '@') {
			PlayerFactory playerFac;
			pc = playerFac.createPlayer(pcRace);
			curCell.setObject(pc);
			v->setPlayer(pc);
			v->notify(*pc);
		}
		else if (sym == '0' || sym == '1' || sym == '2' || sym == '3' || sym == '4' || sym == '5') {
			curPotion++;
			PotionFactory pf;
			shared_ptr<Potion> p = pf.createPotion(sym);
			items.emplace_back(p);
			curCell.setObject(p);
			v->notify(*p);
		} 
		else if (sym == '6' || sym == '7' || sym == '8' || sym == '9') {
			curGold++;
			GoldFactory gf;
			shared_ptr<Gold> g = gf.createGold(sym);
			items.emplace_back(g);
			curCell.setObject(g);
			v->notify(*g);
		} 
		else if (sym == 'H' || sym == 'E' || sym == 'W' || sym == 'O' || sym == 'M' || sym == 'L') {
			curEnemies++;
			EnemyFactory ef;
			shared_ptr<EnemyCharacter> e = ef.createEnemy(sym);
			enemies.emplace_back(e);
			curCell.setObject(e);
			v->notify(*e);
		}
		
		chambers.back().addCell(curCell);
		if (cor.y > 0) {
			if (cor.x > 0) getChamber(maps.at(floor).at(cor.y - 1).at(cor.x - 1), pcRace);
			getChamber(maps.at(floor).at(cor.y - 1).at(cor.x), pcRace);
			if (cor.x < col) getChamber(maps.at(floor).at(cor.y - 1).at(cor.x + 1), pcRace);
		}
		if (cor.y < row) {
			if (cor.x > 0) getChamber(maps.at(floor).at(cor.y + 1).at(cor.x - 1), pcRace);
			getChamber(maps.at(floor).at(cor.y + 1).at(cor.x), pcRace);
			if (cor.x < col) getChamber(maps.at(floor).at(cor.y + 1).at(cor.x + 1), pcRace);
		}	
		if (cor.x > 0) getChamber(maps.at(floor).at(cor.y).at(cor.x - 1), pcRace);
		if (cor.x < col) getChamber(maps.at(floor).at(cor.y).at(cor.x + 1), pcRace);
		
	}
}

void Map::init(char pcRace) {
	race = pcRace;
	floor++;
	numChamber = 0;
	curEnemies = 0;
	curGold = 0;
	curPotion = 0;

	v->setRace(pcRace);

	vector<vector<Cell>> &theMap= maps.at(floor);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Cell &curCell = theMap.at(i).at(j);
			char sym = curCell.getSymbol();
			if (sym != ' ' && sym != '+' && sym != '#' && sym != '-' && sym != '|' && !curCell.getCounted()) {
				numChamber++;
				Chamber chamb;
				chambers.emplace_back(chamb);
				getChamber(curCell, pcRace); 
			}
		}
	}

	if (!stair) { // Create the stair if it is not pre-defined
		CellCorFactory ccf;

		while (true) {
			int chamberNum = ccf.getChamberNum(numChamber);
			Coordinate cellCor = ccf.getCoordinate(chambers.at(chamberNum));
			Cell &theCell = maps.at(floor).at(cellCor.y).at(cellCor.x);
			if (!theCell.getFilled()) {
				stair = make_shared<Stair>(floor, chamberNum);
				theCell.setObject(stair);
				v->notify(*stair);
				break;
			}
		}
	}

	if (!pc) { // create playercharacter if it is not pre-defined
		PlayerFactory pf;
		CellCorFactory ccf;
		int stairChamb = stair->getChamb();

		while (true) {
			int chamberNum = ccf.getChamberNum(numChamber);
			if (chamberNum == stairChamb) continue;
			Coordinate cellCor = ccf.getCoordinate(chambers.at(chamberNum));
			Cell &theCell = maps.at(floor).at(cellCor.y).at(cellCor.x);
			if (!theCell.getFilled()) {
				pc = pf.createPlayer(pcRace);
				theCell.setObject(pc);
				v->setPlayer(pc);
				v->notify(*pc);
				break;
			}
		}
	}

	createPotions(maxPotion - curPotion);
	createGolds(maxGold - curGold);
	createEnemies(maxEnemies - curEnemies);
}

void Map::freeze() {
	f = (f) ? false : true;
}

ostream &operator<<(ostream &out, const Map &m) {
	out << *(m.v);
	return out;
}
