#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "object.h"
#include "state.h"
#include "player.h"
#include "objecttype.h"

class PlayerCharacter;
class Shade;
class Drow;
class Vampire;
class Goblin;
class Troll;

class EnemyCharacter: public Object {
  State state {0, 0, 0};
  int randNum(int min = 0, int max = 101);
protected:
  void setState(float hp, float attack, float defense);
  bool chance(int percent);
  float basicDamage(EnemyCharacter &attacker, PlayerCharacter &defender) const;
  void basicAttack(PlayerCharacter *whoAttacked);
public:
  State getState();
  void loseHp(float n);
  EnemyType enemyType;

  EnemyCharacter(char symb, EnemyType enemyType);
  bool isAlive();
  virtual bool getAttacked(PlayerCharacter &whoFrom) = 0;
  bool getAttacked(EnemyCharacter &whoFrom) override;
  void move(Coordinate &co);

  virtual void attack(Shade &whoAttacked);
  virtual void attack(Drow &whoAttacked);
  virtual void attack(Vampire &whoAttacked);
  virtual void attack(Troll &whoAttacked);
  virtual void attack(Goblin &whoAttacked);
};

class Human: public EnemyCharacter {
public:
	Human(char symb);
	bool getAttacked(PlayerCharacter &whoFrom) override;
};

class Dwarf: public EnemyCharacter {
public:
	Dwarf(char symb);
	bool getAttacked(PlayerCharacter &whoFrom) override;
};

class Elf: public EnemyCharacter {
public:
	Elf(char symb);
	bool getAttacked(PlayerCharacter &whoAttacked) override;
	void elfBasicAttack(PlayerCharacter *whoAttacked);
	void attack(Shade &whoAttacked) override;
	void attack(Vampire &whoAttacked) override;
	void attack(Troll &whoAttacked) override;
	void attack(Goblin &whoAttacked) override;
};

class Halfling: public EnemyCharacter {
public:
	Halfling(char symb);
	bool getAttacked(PlayerCharacter &whoFrom) override;
};

class Orc: public EnemyCharacter {
public:
	Orc(char symb);
	bool getAttacked(PlayerCharacter &whoFrom) override;
	void attack(Goblin &whoAttacked) override;
};

class Merchant: public EnemyCharacter {
public:
  static bool isHostile;
  Merchant(char symb);
  bool getAttacked(PlayerCharacter &whoFrom) override;
};

class Dragon: public EnemyCharacter {
public:
	Dragon(char symb);
	bool getAttacked(PlayerCharacter &whoFrom) override;
};


#endif
