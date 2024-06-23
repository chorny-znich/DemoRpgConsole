#pragma once
#include "player.h"
#include "enemy.h"

enum class BattleActions {
  ATTACK,
  STRONG_ATTACK
};
const size_t STRONG_ATTACK_MODIFIER = 3;
const size_t STRONG_DAMAGE_MODIFIER = 2;

class BattleAction
{
private:
  BattleActions mAction;
  Player& mPlayer;
  Enemy* mpCurrentEnemy;

  static inline BattleAction* mpInstance{ nullptr };

public:
  BattleAction(Player& player);
  static void setAction(BattleActions action);
  static BattleActions getAction();
  void setCurrentEnemy(Enemy* enemy);
  static Enemy* getCurrentEnemy();
  static Player& getPlayer();
};