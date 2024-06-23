#include "battle_action.h"
#include <cassert>

BattleAction::BattleAction(Player& player) :
  mAction{ BattleActions::ATTACK },
  mPlayer{player},
  mpCurrentEnemy{nullptr}
{
  assert(mpInstance == nullptr);
  mpInstance = this;
}

void BattleAction::setAction(BattleActions action)
{
  mpInstance->mAction = action;
}

void BattleAction::setCurrentEnemy(Enemy* enemy)
{
  mpInstance->mpCurrentEnemy = enemy;
}

Enemy* BattleAction::getCurrentEnemy()
{
  return mpInstance->mpCurrentEnemy;
}

Player& BattleAction::getPlayer()
{
  return mpInstance->mPlayer;
}

BattleActions BattleAction::getAction()
{
  return mpInstance->mAction;
}