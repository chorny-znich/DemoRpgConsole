#include "ingridient.h"
#include <DisRealityGF.h>

Ingridient::Ingridient() :
  GameObject(GameObjectType::CONSUMABLE, GameObjectSubType::INGRIDIENT)
{
  setSymbol(IMAGE);
  setType();
  setAmount(dr::EngineUtility::getRandomInRange(1, AMOUNT_RANGE));
}

void Ingridient::setType()
{
  size_t randomType = dr::EngineUtility::getRandomInRange(1, INGRIDIENT_TYPE_NUMBER);
  switch (randomType) {
  case 1:
    mType = IngridientType::FOOD;
    setName("Food");
    break;
  case 2:
    mType = IngridientType::IRON;
    setName("Iron");
    break;
  case 3:
    mType = IngridientType::WOOD;
    setName("Wood");
    break;
  }
}