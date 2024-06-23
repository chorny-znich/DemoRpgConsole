#include "armor.h"

Armor::Armor() :
  GameObject(GameObjectType::ARMOR, GameObjectSubType::CHEST),
  mArmor{0}
{
  setSymbol(IMAGE);
}

void Armor::setArmor(size_t value)
{
  mArmor = value;
}

size_t Armor::getArmor() const
{
  return mArmor;
}