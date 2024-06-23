#include "weapon.h"

Weapon::Weapon(GameObjectSubType type) :
  GameObject(GameObjectType::WEAPON, GameObjectSubType::SWORD)
{
  setSymbol(IMAGE);
  setSubType(type == GameObjectSubType::MELEE ? GameObjectSubType::MELEE : GameObjectSubType::RANGED);
}

void Weapon::setDamage(sf::Vector2u dmg)
{
  mDamage = dmg;
}

sf::Vector2u Weapon::getDamage() const
{
  return mDamage;
}

void Weapon::setWeaponType(WeaponType type)
{
  mWeaponType = type;
}

WeaponType Weapon::getWeaponType() const
{
  return mWeaponType;
}

void Weapon::setWeaponDistance(size_t distance)
{
  mWeaponDistance = distance;
}

size_t Weapon::getWeaponDistance() const
{
  return mWeaponDistance;
}
