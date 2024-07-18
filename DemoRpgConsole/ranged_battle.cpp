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
    direction = { 0, -1 };
  }
  else if (mDirection == GameData::Direction::EAST) {
    direction = { 1, 0 };
  }
  else if (mDirection == GameData::Direction::SOUTH) {
    direction = { 0, 1 };
  }
  else if (mDirection == GameData::Direction::WEST) {
    direction = { -1, 0 };
  }

  std::shared_ptr<Weapon> pRangedWeapon = std::static_pointer_cast<Weapon>(CurrentMapData::getEquipment().getEquipObject("Ranged weapon"));
  if (pRangedWeapon != nullptr) {
    resultMessage = std::format("You shoot with a {}.", pRangedWeapon->getName());
    GameData::Position startPosition = CurrentMapData::getPlayer().getPosition();
    sf::Vector2u mapSize = CurrentMapData::getMapSize();
    int startIndex = startPosition.first + startPosition.second * mapSize.x;
    for (size_t i = 1; i <= pRangedWeapon->getWeaponDistance(); i++) {
      size_t position = startIndex + i * (direction.x + direction.y * static_cast<int>(mapSize.x));
      // a case when the hero hit an enemy
      if (mLocations.at(position).isEnemy()) {
        // check if the player hit the enemy
        Enemy* currentEnemy{ nullptr };
        for (auto& enemy : mEnemies) {
          if (enemy.getPosition().first + enemy.getPosition().second * static_cast<int>(mapSize.x) ==
            position) {
            currentEnemy = &enemy;
            resultMessage += std::format("You attack {}", currentEnemy->getName());
            break;
          }
        }
        int attackMod{ 0 };
        int damageMod{ 0 };
        size_t rollAttack = dr::EngineUtility::getRandomInRange(GameData::DICE.x, GameData::DICE.y);
        resultMessage += std::format(" [dice:{} + Atk:{} + mod: {} vs Enemy Def:{}]\n", rollAttack,
          mPlayer.getSecondaryStatValue("Ranged attack"), attackMod, currentEnemy->getSecondaryStatValue("Defence"));
        if (mPlayer.getSecondaryStatValue("Ranged attack") + rollAttack + attackMod >=
          currentEnemy->getSecondaryStatValue("Defence")) {
          size_t damage = mPlayer.getRangedDamageValue();
          size_t totalDamage = damage + damageMod;
          currentEnemy->decreaseHealth(totalDamage);
          if (currentEnemy->getHealth() == 0) {
            resultMessage += std::format("You deal {} ({}+{}) points of damage.You kill {}", totalDamage, 
              damage, damageMod, currentEnemy->getName());
            currentEnemy->setBattleStatus(false);
            currentEnemy->setActiveStatus(false);
            currentEnemy->isDead();
            mPlayer.increaseExperience(currentEnemy->getExperienceForKill());
            if (mPlayer.levelupCheck()) {
              resultMessage += std::format("\nYou gained new level!");
            }
          }
          else {
            resultMessage += std::format("You deal {} ({}+{}) points of damage. {} has {} points of health",
              totalDamage, damage, damageMod, currentEnemy->getName(), currentEnemy->getHealth());
          }
        break;
        }
        else {
          resultMessage += "You missed the target";
          break;
        }
      }
      // a case when the hero hit an obstacle
      else if (mLocations.at(position).isBarrier()) {
        resultMessage = "You hit an obstacle";
        break;
      }
    }
  }
  else {
    resultMessage = "You don't have a ranged weapon\n";
  }

  return resultMessage;
}
