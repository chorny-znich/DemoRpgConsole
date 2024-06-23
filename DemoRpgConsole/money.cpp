#include "money.h"
#include <DisRealityGF.h>

Money::Money() :
  GameObject{GameObjectType::MONEY, GameObjectSubType::NONE}
{
  setSymbol(IMAGE);
  setAmount();
}

void Money::setAmount()
{
  mAmount = dr::EngineUtility::getRandomInRange(1, 10);
}

size_t Money::getAmount() const
{
  return mAmount;
}