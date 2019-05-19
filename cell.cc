#include "cell.h"
#include "object.h"

using namespace std;

Cell::Cell(char symbol, bool isWall, Coordinate cor, bool isEnemyPath): obj{nullptr}, symbol{symbol}, 
isWall{isWall}, isCounted{false}, cor{cor}, isFilled{false}, isEnemyPath{isEnemyPath} {}

shared_ptr<Object> Cell::getObject() {
	return obj;
}

char Cell::getSymbol() {
	return symbol;
}

void Cell::setSymbol(char sym) {
	symbol = sym;
}

bool Cell::getCounted() {
	return isCounted;
}

void Cell::setCounted() {
	isCounted = true;
}

void Cell::setObject(shared_ptr<Object> newObj) {
	obj = newObj;
	if (newObj) {
		obj->setCoordinate(cor);
		isFilled = true;
	} 
}

bool Cell::getFilled() {
	return isFilled;
}

Coordinate Cell::getCor() {
	return cor;
}

bool Cell::getIsWall() {
	return isWall;
}

bool Cell::getIsEnemyPath() {
	return isEnemyPath;
}
