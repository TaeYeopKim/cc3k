#ifndef _POTIONFACTORY_H_
#define _POTIONFACTORY_H_

#include <memory>

class Potion;

class PotionFactory {
public:
	std::shared_ptr<Potion> createPotion();
	std::shared_ptr<Potion> createPotion(char kind);
};

#endif;
