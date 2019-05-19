#ifndef _ENEMYFACTORY_H_
#define _ENEMYFACTORY_H_

#include <memory>

class EnemyCharacter;

class EnemyFactory {
public:
	std::shared_ptr<EnemyCharacter> createEnemy();
	std::shared_ptr<EnemyCharacter> createEnemy(char race);
};

#endif;
