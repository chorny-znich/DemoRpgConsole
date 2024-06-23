#pragma once

#include "game_object.h"

class Money : public GameObject
{
private:
  const char IMAGE{ '$' };
  size_t mAmount{ 0 };

  void setAmount();

public:
  Money();
  size_t getAmount() const;
};