#ifndef _GOLDFACTORY_H_
#define _GOLDFACTORY_H_

#include <memory>

class Gold;

class GoldFactory {
public:
	std::shared_ptr<Gold> createGold();
	std::shared_ptr<Gold> createGold(char num);
};

#endif;
