#ifndef _VIEW_H_
#define _VIEW_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Object;
class PlayerCharacter;

class View {
	std::vector<std::vector<std::vector<char>>> games;
	size_t gridRow;
	size_t gridCol;
	size_t floor;
	std::string race;
	std::shared_ptr<PlayerCharacter> pc;
	bool inPassage;
	bool onDoor;
public:
	View(std::string fileName);
	void notify(Object &whoFrom);
	void setRace(char newRace);
	void setPlayer(std::shared_ptr<PlayerCharacter> newPc);
	void goUpAFloor();

	friend std::ostream &operator<<(std::ostream &out, const View &v);

};

#endif
