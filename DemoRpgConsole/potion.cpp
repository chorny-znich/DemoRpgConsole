#include "potion.h"
#include "iostream"
#include <DisRealityGF.h>

Potion::Potion() :
  GameObject(GameObjectType::POTION, GameObjectSubType::NONE)
{
  setSymbol(IMAGE);
}

size_t Potion::drink()
{
  std::cout << "You drink the potion\n";

  return 0;
}

HealingPotion::HealingPotion()
{
  setSubType(GameObjectSubType::HEALING_POTION);
}

size_t HealingPotion::drink()
{
  std::cout << "You drink the healing potion\n";

  return HEALING_AMOUNT;
}