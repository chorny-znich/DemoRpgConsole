#pragma once
#include "game_object.h"

/**
 * @brief Danger objects that can hurt a hero
*/
class Trap : public GameObject
{
private:
  const char IMAGE{ '~' };
  sf::Vector2u mDamage{ 1, 1 };
  size_t mDifficulty{ 1 };
public:
  Trap();
  void activate();
  void setDamage(sf::Vector2u damage);
  sf::Vector2u getDamage() const;
  void setDifficulty(size_t difficulty);
  size_t getDifficulty() const;
};