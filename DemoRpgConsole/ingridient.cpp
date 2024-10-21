#include "ingridient.h"
#include <DisRealityGF.h>

Ingridient::Ingridient() :
  GameObject(GameObjectType::CONSUMABLE, GameObjectSubType::INGRIDIENT)
{
  setSymbol(IMAGE);
  setAmount();
}

void Ingridient::setAmount()
{
  size_t randomType = dr::EngineUtility::getRandomInRange(1, INGRIDIENT_TYPE_NUMBER);
  switch (randomType) {
  case 1:
    mType = IngridientType::FOOD;
    break;
  case 2:
    mType = IngridientType::IRON;
    break;
  case 3:
    mType = IngridientType::WOOD;
    break;
  }
   
  mAmount = dr::EngineUtility::getRandomInRange(1, AMOUNT_RANGE);
}

size_t Ingridient::getAmount() const
{
  return mAmount;
}
