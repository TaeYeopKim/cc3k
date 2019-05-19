#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <memory>
#include "view.h"
#include "coordinate.h"
#include "state.h"
#include "object.h"
#include "player.h"
#include "potion.h"

using namespace std;

View::View(string fileName): gridRow{0}, gridCol{0}, floor{0}, race{""}, pc{nullptr}, inPassage{false}, onDoor{false} {
	ifstream file(fileName);
	string line;

	int tmpRow = 0;
	int count = 0;
	int floorCount = 0;

	while (floorCount < 5) {
		getline(file, line);
		gridCol = line.length();

		if (line[0] == '|' && line[1] == '-' && count % 2 == 1) {
			int i = 0;
			vector<char> cellVec;
			games.at(floorCount).emplace_back(cellVec);
			for (char &c: line) {
				bool isWall = (c == ' ' || c == '|' || c == '-' || c == '+') ? true : false;
				games.at(floorCount).back().emplace_back(c);
				i++;
			}
			tmpRow++;

			count++;
			floorCount++;
			gridRow = tmpRow;
			tmpRow = 0;
		} else if (line[0] == '|' && line[1] == '-' && count % 2 == 0) {
			vector<vector<char>> vec;
			games.emplace_back(vec);

			int i = 0;
			vector<char> cellVec;
			games.at(floorCount).emplace_back(cellVec);
			for (char &c: line) {
				bool isWall = (c == ' ' || c == '|' || c == '-' || c == '+') ? true : false;
				games.at(floorCount).back().emplace_back(c);
				i++;
			}
			tmpRow++;
		} else {
			int i = 0;
			vector<char> cellVec;
			games.at(floorCount).emplace_back(cellVec);
			for (char &c: line) {
				bool isWall = (c == ' ' || c == '|' || c == '-' || c == '+') ? true : false;
				games.at(floorCount).back().emplace_back(c);
				i++;
			}
			tmpRow++;
			count++;
		}
	}

	file.close();
}

void View::notify(Object &whoFrom) {
	Coordinate cur = whoFrom.getCurCoordinate();
	Coordinate old = whoFrom.getOldCoordinate();

	if (whoFrom.type == ObjectType::Potion) {
		Potion *pot = dynamic_cast<Potion *>(&whoFrom);
		if (pot->getIsConsumed()) {
			games.at(floor).at(cur.y).at(cur.x) = '.';
			return;
		}
	}

	if (old.x > -1 && old.y > -1) games.at(floor).at(old.y).at(old.x) = '.';

	if (whoFrom.type == ObjectType::Player) {

		if (onDoor) {
			games.at(floor).at(old.y).at(old.x) = '+';
			onDoor = false;
		} else if (inPassage) {
			games.at(floor).at(old.y).at(old.x) = '#';
			inPassage = false;
		}

		if (games.at(floor).at(cur.y).at(cur.x) == '#')	inPassage = true;
		else if (games.at(floor).at(cur.y).at(cur.x) == '+') onDoor = true;
	}

	games.at(floor).at(cur.y).at(cur.x) = whoFrom.getSymb();
}

void View::setRace(char newRace) {
	if (newRace == 's')	race = "Shade";
	else if (newRace == 'v') race = "Vampire";
	else if (newRace == 't') race = "Troll";
	else if (newRace == 'd') race = "Drow";
	else race = "Goblin";
}

void View::setPlayer(shared_ptr<PlayerCharacter> newPc) {
	pc = newPc;
}

void View::goUpAFloor() {
	floor++;
}

ostream &operator<<(ostream &out, const View &v) {
	vector<vector<char>> theGame = v.games.at(v.floor);

	for (auto &r: theGame) {
		for (auto &c: r) {
			out << c;
		}
		out << endl;
	}

	State curState = v.pc->getState();
	string empty((v.gridCol - 24 - v.race.length()), ' ');

	string raceLine = "Race: " + v.race + " Gold: " + to_string(v.pc->getGold()) + empty + "Floor: " + to_string(v.floor + 1);
	string hpLine = "HP: " + to_string(static_cast<int>(curState.hp));
	string atkLine = "Atk: " + to_string(static_cast<int>(curState.attack));
	string defLine = "Def: " + to_string(static_cast<int>(curState.defense));
	string actionLine = "Action: ";

	cout << raceLine << endl;
	cout << hpLine << endl;
	cout << atkLine << endl;
	cout << defLine << endl;
	cout << actionLine << endl;

	return out;
}


