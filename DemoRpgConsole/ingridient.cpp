#include "ingridient.h"
#include <DisRealityGF.h>

void Ingridient::setAmount()
{
  mAmount = dr::EngineUtility::getRandomInRange(1, AMOUNT_RANGE);
}

Ingridient::Ingridient() :
  GameObject(GameObjectType::CONSUMABLE, GameObjectSubType::INGRIDIENT)
{
  setSymbol(IMAGE);
  setAmount();
}

size_t Ingridient::getAmount() const
{
  return mAmount;
}
