#pragma once

#include "game_object.h"

enum class WeaponType {
  MELEE,
  RANGED
};

class Weapon : public GameObject
{
private:
  const char IMAGE{ '?' };
  sf::Vector2u mDamage{};
  WeaponType mWeaponType;
  size_t mWeaponDistance;

public:
  Weapon(GameObjectSubType type);
  void setDamage(sf::Vector2u dmg);
  sf::Vector2u getDamage() const;
  void setWeaponType(WeaponType type);
  WeaponType getWeaponType() const;
  void setWeaponDistance(size_t distance);
  size_t getWeaponDistance() const;
};