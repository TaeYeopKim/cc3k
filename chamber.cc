#include "chamber.h"

Chamber::Chamber(): numCell{0} {}

Cell &Chamber::getCell(Coordinate cor) {
	int len = chamber.size();
	for (int i = 0; i < len; i++) {
		Cell &c = *(chamber.at(i));
		Coordinate cor2 = c.getCor();
		if (cor.x == cor2.x && cor.y == cor2.y) return c;
	}
}

Cell &Chamber::getIndexCell(int i) {
	return *(chamber.at(i));
}

int Chamber::getNumCell() {
	return numCell;
}

void Chamber::addCell(Cell &c) {
	chamber.emplace_back(&c);
	numCell++;
}

