#pragma once

#include "player.h"
#include "enemy.h"
#include "battle_action.h"
#include <string>

class Battle
{ 
private:
  Player& mPlayer;
  Enemy& mEnemy;

public:
  Battle(Player& player, Enemy& enemy);
  std::string playerAttack(BattleActions action);
  std::string enemyAttack(); 
};