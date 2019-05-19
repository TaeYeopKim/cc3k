#ifndef _CHAMBER_H_
#define _CHAMBER_H_

#include <vector>
#include "cell.h"
#include "coordinate.h"

class Chamber {
	std::vector<Cell *> chamber;
	int numCell;
public:
	Chamber();
	Cell &getCell(Coordinate cor);
	Cell &getIndexCell(int i);
	void addCell(Cell &c);
	int getNumCell();
};

#endif

