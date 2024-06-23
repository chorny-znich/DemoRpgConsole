#pragma once

#include "game_object.h"

class Potion : public GameObject
{
protected:
  const char IMAGE{ '*' };

public:
  Potion();
  virtual size_t drink();
};

class HealingPotion : public Potion
{
private:
  const size_t HEALING_AMOUNT = 10;

public:
  HealingPotion();
  virtual size_t drink() override;
};