#pragma once
#include "CurrentMapData.h"
#include "game_data.h"
#include "enemy_manager.h"

/**
 * @brief a player shoot in certain direction
*/
class RangedBattle
{
private:
  Player& mPlayer;
  std::vector<Enemy>& mEnemies;
  std::vector<Location>& mLocations;
  GameData::Direction mDirection;
public:
  RangedBattle(GameData::Direction dir);
  std::string shoot();
};