#include <iostream>

#include "object.h"
#include "coordinate.h"

using namespace std;

Object::Object(char newSymb, ObjectType type) : cur{ Coordinate{-1, -1} }, old{ Coordinate {-1, -1} }, symb{ newSymb }, type{ type } {}

Object::~Object() {}

void Object::setCoordinate(Coordinate cur) {
	old = this->cur;
	this->cur = cur;
}

Coordinate Object::getCurCoordinate() {
	return cur;
}

Coordinate Object::getOldCoordinate() {
	return old;
}

void Object::setDead() {
	symb = '.';
}

char Object::getSymb() {
	return symb;
}

