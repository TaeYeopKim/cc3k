#ifndef _POTION_H_
#define _POTION_H_

#include "object.h"
#include "player.h"
#include "objecttype.h"


class Potion : public Object {
	bool isConsumed;
public:
	const PotionType potionType;

	Potion(PotionType potionType);
	virtual ~Potion();
	bool getAttacked(EnemyCharacter &whoFrom) override;
	bool getAttacked(PlayerCharacter &whoFrom) override;

	void setIsConsumed(bool newConsumed);
	bool getIsConsumed();

	virtual float getHpChange();
	virtual float getAttackChange();
	virtual float getDefenseChange();
};

class BoostAtk : public Potion {
public:
	BoostAtk();
	float getAttackChange() override;
};

class BoostDef : public Potion {
public:
	BoostDef();
	float getDefenseChange() override;
};

class WoundAtk : public Potion {
public:
	WoundAtk();
	float getAttackChange() override;
};

class WoundDef : public Potion {
public:
	WoundDef();
	float getDefenseChange() override;
};

class RestoreHealth : public Potion {
public:
	RestoreHealth();
	float getHpChange() override;
};

class PoisonHealth : public Potion {
public:
	PoisonHealth();
	float getHpChange() override;
};

#endif
