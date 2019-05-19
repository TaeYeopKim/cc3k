#ifndef _PLAYERFACTORY_H_
#define _PLAYERFACTORY_H_
#include <memory>

class PlayerCharacter;

class PlayerFactory {
public:
	std::shared_ptr<PlayerCharacter> createPlayer(char race);
};

#endif;
