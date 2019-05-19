#include "potion.h"

Potion::Potion(PotionType potionType) : Object{ 'P', ObjectType::Potion }, potionType{ potionType }, isConsumed{ false } {}
Potion::~Potion() {}
bool Potion::getAttacked(EnemyCharacter & whoFrom)
{
	return false;
}
bool Potion::getAttacked(PlayerCharacter & whoFrom)
{
	return false;
}

void Potion::setIsConsumed(bool newConsumed) {
	isConsumed = newConsumed;
}

bool Potion::getIsConsumed() {
	return isConsumed;
}

float Potion::getHpChange()
{
	return 0.0f;
}
float Potion::getAttackChange()
{
	return 0.0f;
}
float Potion::getDefenseChange()
{
	return 0.0f;
}


BoostAtk::BoostAtk(): Potion { PotionType::BoostAtk }
{
}
BoostDef::BoostDef() : Potion{ PotionType::BoostDef }
{
}
WoundAtk::WoundAtk() : Potion{ PotionType::WoundAtk }
{
}
WoundDef::WoundDef() : Potion{ PotionType::WoundDef }
{
}
RestoreHealth::RestoreHealth() : Potion{ PotionType::RestoreHealth }
{
}
PoisonHealth::PoisonHealth() : Potion{ PotionType::PoisonHealth }
{
}

// --- Subclasses ----
float BoostAtk::getAttackChange()
{
	return 5.0f;
}

float BoostDef::getDefenseChange()
{
	return 5.0f;
}

float WoundAtk::getAttackChange()
{
	return -5.0f;
}

float WoundDef::getDefenseChange()
{
	return -5.0f;
}

float RestoreHealth::getHpChange()
{
	return 5.0f;
}

float PoisonHealth::getHpChange()
{
	return -5.0f;
}
