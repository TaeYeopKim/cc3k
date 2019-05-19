#include "player.h"
#include <cmath>
#include <memory>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

State PlayerCharacter::getState() {
	return state;
}
void PlayerCharacter::setState(float hp, float attack, float defense) {
	state.hp = hp;
	state.attack = attack;
	state.defense = defense;
}

void PlayerCharacter::gainHp(float n) {
	if (hpLimit < state.hp + n) state.hp = hpLimit;
	else if (state.hp + n < 0) state.hp = 0;
	else state.hp += n;
}
void PlayerCharacter::loseHp(float n)
{
	gainHp(-n);
}
void PlayerCharacter::gainAtk(float n) {
	if (state.attack + n < 0) state.attack = 0;
	else state.attack += n;
}
void PlayerCharacter::loseAtk(float n)
{
	gainAtk(-n);
}
void PlayerCharacter::gainDef(float n) {
	if (state.defense + n < 0) state.defense = 0;
	state.defense += n;
}
void PlayerCharacter::loseDef(float n)
{
	gainDef(-n);
}
float PlayerCharacter::getOrigAtk() {
	return origAtk;
}
float PlayerCharacter::getOrigDef() {
	return origDef;
}
void PlayerCharacter::setOrigAtk(float n) {
	origAtk = n;
}
void PlayerCharacter::setOrigDef(float n) {
	origDef = n;
}

void PlayerCharacter::gainGold(int n) {
	gold += n;
}
void PlayerCharacter::gainHpLimit(float n) {
	hpLimit += n;
}
float PlayerCharacter::getHpLimit() {
	return hpLimit;
}
void PlayerCharacter::floorReset() {
	setState(getState().hp, getOrigAtk(), getOrigDef());
}

std::string PlayerCharacter::getLatestActionMessage()
{
	return "Not yet implemented";
}

float PlayerCharacter::basicDamage(PlayerCharacter &attacker, EnemyCharacter &defender) const {
	return ceil((100 / (100 + defender.getState().defense)) * attacker.getState().attack);
}
void PlayerCharacter::basicAttack(EnemyCharacter *whoAttacked) {
	float damage = basicDamage(*this, *whoAttacked);
	whoAttacked->loseHp(damage);
}

PlayerCharacter::PlayerCharacter(): Object{'@', ObjectType::Player }, gold{ 0 }, hpLimit{ 0 } {
}
bool PlayerCharacter::isAlive() {
	return getState().hp > 0.0f;
}
int PlayerCharacter::getGold() {
	return gold;
}
bool PlayerCharacter::getAttacked(PlayerCharacter &whoFrom) {
	return false;;
}
void PlayerCharacter::move(Coordinate &co) {}

void PlayerCharacter::attack(Human &whoAttacked) {
	basicAttack(&whoAttacked);
}
void PlayerCharacter::attack(Dwarf &whoAttacked) {
	basicAttack(&whoAttacked);
}
void PlayerCharacter::attack(Elf &whoAttacked) {
	basicAttack(&whoAttacked);
}
void PlayerCharacter::attack(Halfling &whoAttacked) {
	basicAttack(&whoAttacked);
}
void PlayerCharacter::attack(Orc &whoAttacked) {
	basicAttack(&whoAttacked);
}
void PlayerCharacter::attack(Merchant &whoAttacked) {
	basicAttack(&whoAttacked);
}
void PlayerCharacter::attack(Dragon &whoAttacked) {
	basicAttack(&whoAttacked);
}

bool PlayerCharacter::doesKnow(Potion & potion)
{
	return (std::find(potionsConsumed.begin(), potionsConsumed.end(), potion.potionType) != potionsConsumed.end());
}
void PlayerCharacter::consume(Potion &whatConsumed) {
	gainHp(whatConsumed.getHpChange());
	gainAtk(whatConsumed.getAttackChange());
	gainDef(whatConsumed.getDefenseChange());
	whatConsumed.setIsConsumed(true);
	if (!doesKnow(whatConsumed)) potionsConsumed.push_back(whatConsumed.potionType);
}
void PlayerCharacter::consume(Gold &whatConsumed) {
	gainGold(whatConsumed.getGold());
}



// --- Shade --------------------------------------
Shade::Shade(): PlayerCharacter{} {
	setState(125, 25, 25);
	gainHpLimit(125);
	setOrigAtk(25);
	setOrigDef(25);
}
bool Shade::getAttacked(EnemyCharacter & whoFrom)
{	
	//(H)uman, d(W)arf, (E)lf, (O)rc, (M)erchant, (D)ragon, Half(L)ing.
	string a = "Enemy";
	if (whoFrom.getSymb() == 'H') a = "Human";
	else if (whoFrom.getSymb() == 'W') a = "Dwarf";
	else if (whoFrom.getSymb() == 'E') a = "Elf";
	else if (whoFrom.getSymb() == 'O') a = "Orc";
	else if (whoFrom.getSymb() == 'M') a = "Merchant";
	else if (whoFrom.getSymb() == 'D') a = "Dragon";
	else if (whoFrom.getSymb() == 'L') a = "Halfling";
	cout << a << " attacked Player damage(";
	whoFrom.attack(*this);
	cout << ") HP(" << getState().hp << ")" << endl;
	if (getState().hp == 0) return true;
	return false;
}

// --- Drow ------------------------------------
Drow::Drow(): PlayerCharacter{} {
	setState(150, 25, 15);
	gainHpLimit(150);
	setOrigAtk(25);
	setOrigDef(15);
	// potion effect magnified 150%
}
bool Drow::getAttacked(EnemyCharacter & whoFrom)
{
	//(H)uman, d(W)arf, (E)lf, (O)rc, (M)erchant, (D)ragon, Half(L)ing.
	string a = "Enemy";
	if (whoFrom.getSymb() == 'H') a = "Human";
	else if (whoFrom.getSymb() == 'W') a = "Dwarf";
	else if (whoFrom.getSymb() == 'E') a = "Elf";
	else if (whoFrom.getSymb() == 'O') a = "Orc";
	else if (whoFrom.getSymb() == 'M') a = "Merchant";
	else if (whoFrom.getSymb() == 'D') a = "Dragon";
	else if (whoFrom.getSymb() == 'L') a = "Halfling";
	cout << a << " attacked Player damage(";
	whoFrom.attack(*this);
	cout << ") HP(" << getState().hp << ")" << endl;
	if (getState().hp == 0) return true;
	return false;
}

void Drow::consume(Potion &whatConsumed) {
	gainHp(1.5f * whatConsumed.getHpChange());
	gainAtk(1.5f * whatConsumed.getAttackChange());
	gainDef(1.5f * whatConsumed.getDefenseChange());
	whatConsumed.setIsConsumed(true);
	if (!doesKnow(whatConsumed)) potionsConsumed.push_back(whatConsumed.potionType);
}

// --- Vampire ------------------------------------
Vampire::Vampire(): PlayerCharacter{} {
	setState(50, 25, 25);
	gainHpLimit(50);
	setOrigAtk(25);
	setOrigDef(25);
}
bool Vampire::getAttacked(EnemyCharacter & whoFrom)
{
	//(H)uman, d(W)arf, (E)lf, (O)rc, (M)erchant, (D)ragon, Half(L)ing.
	string a = "Enemy";
	if (whoFrom.getSymb() == 'H') a = "Human";
	else if (whoFrom.getSymb() == 'W') a = "Dwarf";
	else if (whoFrom.getSymb() == 'E') a = "Elf";
	else if (whoFrom.getSymb() == 'O') a = "Orc";
	else if (whoFrom.getSymb() == 'M') a = "Merchant";
	else if (whoFrom.getSymb() == 'D') a = "Dragon";
	else if (whoFrom.getSymb() == 'L') a = "Halfling";
	cout << a << " attacked Player damage(";
	whoFrom.attack(*this);
	cout << ") HP(" << getState().hp << ")" << endl;
	if (getState().hp == 0) return true;
	return false;
}

void Vampire::attack(Human &whoAttacked) {
	cout << "Player attacked Human damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHpLimit(5);
	gainHp(5);
}
void Vampire::attack(Dwarf &whoAttacked) {
	cout << "Player attacked Dwarf damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHp(-5);
}
void Vampire::attack(Elf &whoAttacked) {
	cout << "Player attacked Elf damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHpLimit(5);
	gainHp(5);
}
void Vampire::attack(Halfling &whoAttacked) {
	cout << "Player attacked Halfling damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHpLimit(5);
	gainHp(5);
}
void Vampire::attack(Orc &whoAttacked) {
	cout << "Player attacked Orc damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHpLimit(5);
	gainHp(5);
}
void Vampire::attack(Merchant &whoAttacked) {
	cout << "Player attacked Merchant damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHpLimit(5);
	gainHp(5);
}
void Vampire::attack(Dragon &whoAttacked) {
	cout << "Player attacked Dragon damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHpLimit(5);
	gainHp(5);
}

void Vampire::consume(Potion &whatConsumed) {
	gainHp(whatConsumed.getHpChange());
	gainAtk(whatConsumed.getAttackChange());
	gainDef(whatConsumed.getDefenseChange());
	gainHpLimit(whatConsumed.getHpChange());
	whatConsumed.setIsConsumed(true);
	if (!doesKnow(whatConsumed)) potionsConsumed.push_back(whatConsumed.potionType);
}

// --- Goblin ---------------------------------------------
Goblin::Goblin(): PlayerCharacter{} {
	setState(110, 15, 20);
	gainHpLimit(110);
	setOrigAtk(15);
	setOrigDef(20);
	// steals 5 gold from every slain enemy
}
bool Goblin::getAttacked(EnemyCharacter & whoFrom)
{
	//(H)uman, d(W)arf, (E)lf, (O)rc, (M)erchant, (D)ragon, Half(L)ing.
	string a = "Enemy";
	if (whoFrom.getSymb() == 'H') a = "Human";
	else if (whoFrom.getSymb() == 'W') a = "Dwarf";
	else if (whoFrom.getSymb() == 'E') a = "Elf";
	else if (whoFrom.getSymb() == 'O') a = "Orc";
	else if (whoFrom.getSymb() == 'M') a = "Merchant";
	else if (whoFrom.getSymb() == 'D') a = "Dragon";
	else if (whoFrom.getSymb() == 'L') a = "Halfling";
	cout << a << " attacked Player damage(";
	whoFrom.attack(*this);
	cout << ") HP(" << getState().hp << ")" << endl;
	if (getState().hp == 0) return true;
	return false;
}

void Goblin::attack(Human &whoAttacked) {
	cout << "Player attacked Human damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	if (!whoAttacked.isAlive()) gainGold(5);
}
void Goblin::attack(Dwarf &whoAttacked) {
	cout << "Player attacked Dwarf damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	if (!whoAttacked.isAlive()) gainGold(5);
}
void Goblin::attack(Elf &whoAttacked) {
	cout << "Player attacked Elf damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	if (!whoAttacked.isAlive()) gainGold(5);
}
void Goblin::attack(Halfling &whoAttacked) {
	cout << "Player attacked Halfling damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	if (!whoAttacked.isAlive()) gainGold(5);
}
void Goblin::attack(Orc &whoAttacked) {
	cout << "Player attacked Orc damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	if (!whoAttacked.isAlive()) gainGold(5);
}
void Goblin::attack(Merchant &whoAttacked) {
	cout << "Player attacked Merchant damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	if (!whoAttacked.isAlive()) gainGold(5);
}
void Goblin::attack(Dragon &whoAttacked) {
	cout << "Player attacked Dragon damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	if (!whoAttacked.isAlive()) gainGold(5);
}

// --- Troll ----------------------------------------------
Troll::Troll(): PlayerCharacter{} {
	setState(120, 25, 15);
	gainHpLimit(120);
	setOrigAtk(25);
	setOrigDef(15);
}
bool Troll::getAttacked(EnemyCharacter & whoFrom)
{
	//(H)uman, d(W)arf, (E)lf, (O)rc, (M)erchant, (D)ragon, Half(L)ing.
	string a = "Enemy";
	if (whoFrom.getSymb() == 'H') a = "Human";
	else if (whoFrom.getSymb() == 'W') a = "Dwarf";
	else if (whoFrom.getSymb() == 'E') a = "Elf";
	else if (whoFrom.getSymb() == 'O') a = "Orc";
	else if (whoFrom.getSymb() == 'M') a = "Merchant";
	else if (whoFrom.getSymb() == 'D') a = "Dragon";
	else if (whoFrom.getSymb() == 'L') a = "Halfling";
	cout << a << " attacked Player damage(";
	whoFrom.attack(*this);
	cout << ") HP(" << getState().hp << ")" << endl;
	if (getState().hp == 0) return true;
	return false;
}
void Troll::move(Coordinate &co) {
	gainHp(5.0f);
}

void Troll::attack(Human &whoAttacked) {
	cout << "Player attacked Human damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHp(5.0f);
}
void Troll::attack(Dwarf &whoAttacked) {
	cout << "Player attacked Dwarf damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHp(5.0f);
}
void Troll::attack(Elf &whoAttacked) {
	cout << "Player attacked Elf damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHp(5.0f);
}
void Troll::attack(Halfling &whoAttacked) {
	cout << "Player attacked Halfling damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHp(5.0f);
}
void Troll::attack(Orc &whoAttacked) {
	cout << "Player attacked Orc damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHp(5.0f);
}
void Troll::attack(Merchant &whoAttacked) {
	cout << "Player attacked Merchant damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHp(5.0f);
}
void Troll::attack(Dragon &whoAttacked) {
	cout << "Player attacked Dragon damage(";
	basicAttack(&whoAttacked);
	cout << ") HP(" << whoAttacked.getState().hp << ")" << endl;
	gainHp(5.0f);
}

void Troll::consume(Potion &whatConsumed) {
	gainHp(5.0f + whatConsumed.getHpChange());
	gainAtk(whatConsumed.getAttackChange());
	gainDef(whatConsumed.getDefenseChange());
	whatConsumed.setIsConsumed(true);
	if (!doesKnow(whatConsumed)) potionsConsumed.push_back(whatConsumed.potionType);
}




