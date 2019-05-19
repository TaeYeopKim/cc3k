#ifndef _CELL_H_
#define _CELL_H_

#include <memory>
#include "coordinate.h"

class Object;

class Cell {
	std::shared_ptr<Object> obj;
	char symbol;
	bool isWall;
	bool isCounted;
	bool isFilled;
	Coordinate cor;
	bool isEnemyPath;
public:
	Cell(char symbol, bool isWall, Coordinate cor, bool isEnemyPath);
	std::shared_ptr<Object> getObject();
	void setObject(std::shared_ptr<Object> obj);
	char getSymbol();
	void setSymbol(char sym);
	bool getCounted();
	void setCounted();
	bool getFilled();
	Coordinate getCor();
	bool getIsWall();
	bool getIsEnemyPath();
};

#endif

