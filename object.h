#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "coordinate.h"
#include "objecttype.h"

class EnemyCharacter;
class PlayerCharacter;

class Object {
	Coordinate cur;
	Coordinate old;
	char symb;
public:
	const ObjectType type;

	Object(char newSymb, ObjectType type);
	virtual ~Object();
	void setCoordinate(Coordinate cur);

	Coordinate getCurCoordinate();
	Coordinate getOldCoordinate();
	char getSymb();
	void setDead();

	virtual bool getAttacked(EnemyCharacter &whoFrom) = 0;
	virtual bool getAttacked(PlayerCharacter &whoFrom) = 0;
};

#endif
