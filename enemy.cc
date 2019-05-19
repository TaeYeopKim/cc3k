#include "enemy.h"
#include <cmath>
#include <time.h> 
#include <stdlib.h>

// only include these for Halfling.cc 
#include <iostream> 
using namespace std;

// --- Enemy character -----------------------------------
int EnemyCharacter::randNum(int min, int max)
{
  return rand() % max + min;
}
State EnemyCharacter::getState() {
  return state;
}
void EnemyCharacter::setState(float hp, float attack, float defense) {
  state.hp = hp;
  state.attack = attack;
  state.defense = defense;
}
void EnemyCharacter::loseHp(float n) {
	if (state.hp - n < 0) state.hp = 0;
	else state.hp -= n;
}

bool EnemyCharacter::chance(int percent) {
  srand(time(0));  
  int num = randNum();
  if (num >= percent) return true;
  return false;
}
float EnemyCharacter::basicDamage(EnemyCharacter &attacker, PlayerCharacter &defender) const {
  return ceil((100 / (100 + defender.getState().defense)) * attacker.getState().attack);
}
void EnemyCharacter::basicAttack(PlayerCharacter *whoAttacked) {
  int damageTaken = basicDamage(*this, *whoAttacked);
  whoAttacked->loseHp(damageTaken);
}

EnemyCharacter::EnemyCharacter(char symb, EnemyType enemyType) : Object{ symb, ObjectType::Enemy }, enemyType{ enemyType } {}
bool EnemyCharacter::isAlive() {
  return getState().hp > 0.0f;
}
bool EnemyCharacter::getAttacked(EnemyCharacter &whoFrom) {
  return false;
}
void EnemyCharacter::move(Coordinate &co) {
  setCoordinate(co);
}

void EnemyCharacter::attack(Shade &whoAttacked) {
  basicAttack(&whoAttacked);
}
void EnemyCharacter::attack(Drow &whoAttacked) {
  basicAttack(&whoAttacked);
}
void EnemyCharacter::attack(Vampire &whoAttacked) {
  basicAttack(&whoAttacked);
}
void EnemyCharacter::attack(Troll &whoAttacked) {
  basicAttack(&whoAttacked);
}
void EnemyCharacter::attack(Goblin &whoAttacked) {
  basicAttack(&whoAttacked);
}

// --- Human -----------------------------------
Human::Human(char symb) : EnemyCharacter{ symb, EnemyType::Human } {
  setState(140, 20, 20);
}
bool Human::getAttacked(PlayerCharacter &whoFrom) {
  whoFrom.attack(*this); 
  if (getState().hp == 0) return true;
  return false;
}

// --- Dwarf -----------------------------------
Dwarf::Dwarf(char symb) : EnemyCharacter{ symb, EnemyType::Dwarf } {
  setState(100, 20, 30);
}
bool Dwarf::getAttacked(PlayerCharacter &whoFrom) {
  whoFrom.attack(*this); 
  if (getState().hp == 0) return true;
  return false;
}

// --- Elf -----------------------------------
Elf::Elf(char symb) : EnemyCharacter{ symb, EnemyType::Elf } {
  setState(140, 30, 10);
}
bool Elf::getAttacked(PlayerCharacter &whoFrom) {
  whoFrom.attack(*this); 
  if (getState().hp == 0) return true;
  return false;
}
// two attacks against every race except for drows
void Elf::elfBasicAttack(PlayerCharacter *whoAttacked) {
  basicAttack(whoAttacked);
  basicAttack(whoAttacked);
}
void Elf::attack(Shade &whoAttacked) {
  elfBasicAttack(&whoAttacked);
}
void Elf::attack(Vampire &whoAttacked) {
  elfBasicAttack(&whoAttacked);
}
void Elf::attack(Troll &whoAttacked) {
  elfBasicAttack(&whoAttacked);
}
void Elf::attack(Goblin &whoAttacked) {
  elfBasicAttack(&whoAttacked);
}

// --- Halfling -----------------------------------
Halfling::Halfling(char symb) : EnemyCharacter{ symb, EnemyType::Halfling } {
  setState(100, 15, 20);
}
bool Halfling::getAttacked(PlayerCharacter &whoFrom) {
  //has 50% chance for the player to miss their attack
  bool hitAttack = chance(50);
  if (hitAttack) { 
    whoFrom.attack(*this); 
  } else {
    cout << "Player missed hitting Halfling" << endl;
  }
  if (getState().hp == 0) return true;
  return false;
}

// --- Orc -----------------------------------
Orc::Orc(char symb) : EnemyCharacter{ symb, EnemyType::Orc } {
  setState(180, 30, 25);
}
bool Orc::getAttacked(PlayerCharacter &whoFrom) {
  whoFrom.attack(*this); 
  if (getState().hp == 0) return true;
  return false;
}
void Orc::attack(Goblin &whoAttacked) {
  int damageTaken = 1.5 * basicDamage(*this, whoAttacked);
  whoAttacked.loseHp(damageTaken);
}

// --- Merchant -----------------------------------
Merchant::Merchant(char symb) : EnemyCharacter{ symb, EnemyType::Merchant } {
  setState(30, 70, 50);
}
bool Merchant::getAttacked(PlayerCharacter &whoFrom) {
  isHostile = true;
  whoFrom.attack(*this); 
  if (getState().hp == 0) return true;
  return false;
}
bool Merchant::isHostile = false;

// --- Dragon -----------------------------------
Dragon::Dragon(char symb) : EnemyCharacter{ symb, EnemyType::Dragon } {
  setState(150, 20, 20);
}
bool Dragon::getAttacked(PlayerCharacter &whoFrom) {
  whoFrom.attack(*this); 
  if (getState().hp == 0) return true;
  return false;
}

