#include "ranged_battle.h"
#include "weapon.h"
#include <iostream>
#include <format>
#include <memory>
#include <DisRealityGF.h>

RangedBattle::RangedBattle(GameData::Direction dir) :
  mPlayer{CurrentMapData::getPlayer()},
  mEnemies{CurrentMapData::getEnemies()},
  mLocations{CurrentMapData::getMap()},
  mDirection{dir}
{
}

std::string RangedBattle::shoot()
{
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
        // check if the player hit the enemy
        Enemy* currentEnemy;
        for (auto& enemy : mEnemies) {
          if (enemy.getPosition().first + enemy.getPosition().second * static_cast<int>(mapSize.x) ==
            position) {
            currentEnemy = &enemy;
          }
        }
        std::string str{ std::format("You attack {}", currentEnemy->getName()) };
        int attackMod{ 0 };
        int damageMod{ 0 };
        size_t rollAttack = dr::EngineUtility::getRandomInRange(GameData::DICE.x, GameData::DICE.y);
        resultMessage = std::format(" [dice:{} + Atk:{} + mod: {} vs Enemy Def:{}]\n", rollAttack,
          mPlayer.getSecondaryStatValue("Ranged attack"), attackMod, currentEnemy->getSecondaryStatValue("Defence"));
        if (mPlayer.getSecondaryStatValue("Ranged attack") + rollAttack + attackMod >= 
          currentEnemy->getSecondaryStatValue("Defence")) {
          size_t damage = mPlayer.getDamageValue();
          size_t totalDamage = damage + damageMod;
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
    resultMessage = "You don't have a ranged weapon\n";
  }

  return resultMessage;
}
