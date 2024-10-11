#pragma once
#include "game_object.h"

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
  const char IMAGE{'!'};
  const char AMOUNT_RANGE = 5;
  size_t mAmount{ 0 };
  IngridientType mType;
  void setAmount();
public:
  Ingridient();
  size_t getAmount() const;
};

