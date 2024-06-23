#pragma once

#include "game_object.h"

class Armor : public GameObject
{
private:
  const char IMAGE{ '?' };
  size_t mArmor;

public:
  Armor();
  void setArmor(size_t value);
  size_t getArmor() const;
};