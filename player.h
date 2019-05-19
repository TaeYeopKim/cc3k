#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "state.h"
#include "enemy.h"
#include "cell.h"
#include "potion.h"
#include "gold.h"
#include "objecttype.h"

#include <list>

class EnemyCharacter;
class Human;
class Dwarf;
class Elf;
class Halfling;
class Orc;
class Merchant;
class Dragon;
class Gold;
class Potion;
class BoostAtk;
class BoostDef;
class WoundAtk;
class WoundDef;
class PoisonHealth;
class RestoreHealth;


class PlayerCharacter: public Object {
	State state {0, 0, 0};
	int gold;
	float hpLimit;
	float origAtk = 0;
	float origDef = 0;
protected:
	std::list<PotionType> potionsConsumed; // keeping track of potion types consumed

	void setState(float hp, float attack, float defense);
	float basicDamage(PlayerCharacter &attacker, EnemyCharacter &defender) const;
	void basicAttack(EnemyCharacter *whoAttacked);
public:
	State getState();
	
	void gainHp(float n);
	void loseHp(float n);
	void gainAtk(float n);
	void loseAtk(float n);
	void gainDef(float n);
	void loseDef(float n);
	float getOrigAtk();
	void setOrigAtk(float n);
	float getOrigDef();
	void setOrigDef(float n);

	int getGold();
	void gainGold(int n);
	void gainHpLimit(float n);	
	float getHpLimit();
	void floorReset();
	std::string getLatestActionMessage();

	PlayerCharacter();	
	bool isAlive();
	virtual bool getAttacked(PlayerCharacter &whoFrom) override;	
	virtual bool getAttacked(EnemyCharacter &whoFrom) = 0;
	virtual void move(Coordinate &co);

	virtual void attack(Human &whoAttacked);
	virtual void attack(Dwarf &whoAttacked);
	virtual void attack(Elf &whoAttacked);
	virtual void attack(Halfling &whoAttacked);
	virtual void attack(Orc &whoAttacked);
	virtual void attack(Merchant &whoAttacked);
	virtual void attack(Dragon &whoAttacked);
	
	virtual bool doesKnow(Potion &potion);
	virtual void consume(Potion &whatConsumed);
	virtual void consume(Gold &whatConsumed);
};

class Shade : public PlayerCharacter {
public:
	Shade();
	bool getAttacked(EnemyCharacter &whoFrom);
};

class Drow : public PlayerCharacter {
public:
	Drow();
	bool getAttacked(EnemyCharacter &whoFrom);

	void consume(Potion &whatConsumed) override;
};

class Vampire : public PlayerCharacter {
public:
	Vampire();
	bool getAttacked(EnemyCharacter &whoFrom);

	void attack(Human &whoAttacked) override;
	void attack(Dwarf &whoAttacked) override;
	void attack(Elf &whoAttacked) override;
	void attack(Halfling &whoAttacked) override;
	void attack(Orc &whoAttacked) override;
	void attack(Merchant &whoAttacked) override;
	void attack(Dragon &whoAttacked) override;

	void consume(Potion &whatConsumed) override;
};

class Goblin : public PlayerCharacter {
public:
	Goblin();
	bool getAttacked(EnemyCharacter &whoFrom);

	void attack(Human &whoAttacked) override;
	void attack(Dwarf &whoAttacked) override;
	void attack(Elf &whoAttacked) override;
	void attack(Halfling &whoAttacked) override;
	void attack(Orc &whoAttacked) override;
	void attack(Merchant &whoAttacked) override;
	void attack(Dragon &whoAttacked) override;
};

class Troll : public PlayerCharacter {
public:
	Troll();
	bool getAttacked(EnemyCharacter &whoFrom);
	void move(Coordinate &co) override;
	
	void attack(Human &whoAttacked) override;
	void attack(Dwarf &whoAttacked) override;
	void attack(Elf &whoAttacked) override;
	void attack(Halfling &whoAttacked) override;
	void attack(Orc &whoAttacked) override;
	void attack(Merchant &whoAttacked) override;
	void attack(Dragon &whoAttacked) override;

	void consume(Potion &whatConsumed) override;
};


#endif
