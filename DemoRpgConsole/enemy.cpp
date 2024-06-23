#include "enemy.h"
#include "DisRealityGF.h"

Enemy::Enemy()
{
  setMaxHealth(10);
}

void Enemy::move()
{
  size_t decision = dr::EngineUtility::getRandomInRange(1, 11);
  if (decision == 1 || decision == 2) {
    mMovement = { 0, 0 };
  }
  else if (decision == 3 || decision == 4) {
    mMovement = { -1, 0 };
  }
  else if (decision == 5 || decision == 6) {
    mMovement = { 1, 0 };
  }
  else if (decision == 7 || decision == 8) {
    mMovement = { 0, 1 };
  }
  else if (decision == 9 || decision == 10) {
    mMovement = { 0, -1 };
  }
}

void Enemy::update()
{
  mPosition.first += mMovement.first;
  mPosition.second += mMovement.second;
}

void Enemy::isDead()
{
  mDead = true;
}

void Enemy::setBattleStatus(bool status)
{
  mInBattle = status;
}

bool Enemy::isInBattle() const
{
  return mInBattle;
}