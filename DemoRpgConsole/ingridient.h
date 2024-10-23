#pragma once
#include "game_object.h"

const size_t INGRIDIENT_TYPE_NUMBER = 3;
enum class IngridientType
{
  FOOD,
  WOOD,
  IRON
};

/**
 * @brief Consumable item for the craft
*/
class Ingridient : public GameObject
{
private:
  const char IMAGE{'"'};
  const char AMOUNT_RANGE = 5;
  IngridientType mType;
  void setType();
public:
  Ingridient();
};