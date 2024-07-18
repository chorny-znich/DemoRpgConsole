#include "arrow.h"
#include <DisRealityGF.h>

Arrow::Arrow() :
  GameObject(GameObjectType::CONSUMABLE, GameObjectSubType::ARROW)
{
  setSymbol(IMAGE);
  setAmount();
}

void Arrow::setAmount()
{
  mAmount = dr::EngineUtility::getRandomInRange(1, AMOUNT_RANGE);
}

size_t Arrow::getAmount() const
{
  return mAmount;
}