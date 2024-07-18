#pragma once
#include "game_object.h"

/**
 * @brief Consumable item for bows
*/
class Arrow : public GameObject
{
private:
  const char IMAGE{ '|' };
  const char AMOUNT_RANGE = 5;
  size_t mAmount{ 0 };

  void setAmount();

public:
  Arrow();
  size_t getAmount() const;
};