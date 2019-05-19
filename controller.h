#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <iostream>
#include <string>
#include "map.h"

class Map;

class Controller {
	std::unique_ptr<Map> m;
	std::string fileName;
public:
	// move, attack, use potion, f, r, q
	Controller(std::string fileName = "cc3kfloor.txt");
	void makeMove(std::string cmd1, std::string cmd2);
	void init(char pc);
	void freeze();
	void restart();
	void quit();

	friend std::ostream &operator<<(std::ostream &out, const Controller &c);
};

#endif

