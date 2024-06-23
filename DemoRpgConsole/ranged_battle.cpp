#include "ranged_battle.h"
#include "weapon.h"
#include <iostream>
#include <format>

RangedBattle::RangedBattle() :
  mPlayer{CurrentMapData::getPlayer()},
  mEnemies{CurrentMapData::getEnemies()},
  mLocations{CurrentMapData::getMap()}
{
}

void RangedBattle::shoot(GameData::Direction dir)
{
  mDirection = dir;
  sf::Vector2i direction;
  std::string resultMessage = "You missed a target";

  if (mDirection == GameData::Direction::NORTH) {
    std::cout << "You are shooting North ";
    direction = { 0, -1 };
  }
  else if (mDirection == GameData::Direction::EAST) {
    std::cout << "You are shooting East ";
    direction = { 1, 0 };
  }
  else if (mDirection == GameData::Direction::SOUTH) {
    std::cout << "You are shooting South ";
    direction = { 0, 1 };
  }
  else if (mDirection == GameData::Direction::WEST) {
      std::cout << "You are shooting West ";
      direction = { -1, 0 };
  }

  std::shared_ptr<Weapon> pRangedWeapon = std::static_pointer_cast<Weapon>(CurrentMapData::getEquipment().getEquipObject("Ranged weapon"));
  if (pRangedWeapon != nullptr) {
    std::cout << std::format("with a {}", pRangedWeapon->getName());
    GameData::Position startPosition = CurrentMapData::getPlayer().getPosition();
    sf::Vector2u mapSize = CurrentMapData::getMapSize();
    int startIndex = startPosition.first + startPosition.second * mapSize.x;
    for (size_t i = 1; i <= pRangedWeapon->getWeaponDistance(); i++) {
      size_t position = startIndex + i * (direction.x + direction.y * static_cast<int>(mapSize.x));
      // a case when the hero hit an enemy
      if (mLocations.at(position).isEnemy()) {
        resultMessage = "You hit an enemy";
        break;
      }
      // a case when the hero hit an obstacle
      else if (mLocations.at(position).isBarrier()) {
        resultMessage = "You hit an obstacle";
        break;
      }
    }
    std::cout << "\n" << resultMessage << "\n";
  }
  else {
    std::cout << "You don't have a ranged weapon\n";
  }
}
