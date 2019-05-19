#ifndef _CELLCORFACTORY_H
#define _CELLCORFACTORY_H

#include "coordinate.h"
#include "chamber.h"

class CellCorFactory {
public:
	Coordinate getCoordinate(Chamber &ch);
	int getChamberNum(int numChamber);
};

#endif

