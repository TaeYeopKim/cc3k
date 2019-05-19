#include "goldFactory.h"
#include "gold.h"
#include <time.h>

using namespace std;

shared_ptr<Gold> GoldFactory::createGold() {
	srand(time(0));

	int randNum = rand() % 8;

	if (randNum == 0 || randNum == 1) {
		return make_shared<Gold>(1);
	} else if (randNum == 3) {
		return make_shared<Gold>(6);
	} else {
		return make_shared<Gold>(2);
	}
}

shared_ptr<Gold> GoldFactory::createGold(char num) {
	if (num == '7') {
		return make_shared<Gold>(1);
	} else if (num == '9') {
		return make_shared<Gold>(6);
	} else if (num == '6') {
		return make_shared<Gold>(2);
	} else {
		return make_shared<Gold>(4);
	}
}
