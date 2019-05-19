#include <iostream>


#include <time.h>
#include "cellCorFactory.h"

Coordinate CellCorFactory::getCoordinate(Chamber &ch) {
	srand(time(0));

	int numChamberCell = ch.getNumCell();
	int randNum = rand() % numChamberCell;

	Cell &chosenCell = ch.getIndexCell(randNum);

	return chosenCell.getCor();
}

int CellCorFactory::getChamberNum(int numChamber) {
	srand(time(0));

	return rand() % numChamber;
}
