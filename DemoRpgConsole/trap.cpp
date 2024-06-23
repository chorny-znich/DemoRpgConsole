#include "trap.h"
#include <iostream>

Trap::Trap() :
  GameObject{ GameObjectType::TRAP, GameObjectSubType::NONE }
{
  setSymbol(IMAGE);
}

void Trap::activate()
{
  std::cout << "You activate a trap\n";
}

void Trap::setDamage(sf::Vector2u damage)
{
  mDamage = damage;
}

sf::Vector2u Trap::getDamage() const
{
  return mDamage;
}

void Trap::setDifficulty(size_t difficulty)
{
  mDifficulty = difficulty;
}

size_t Trap::getDifficulty() const
{
  return mDifficulty;
}
