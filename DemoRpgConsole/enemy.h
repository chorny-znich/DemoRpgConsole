#pragma once

#include "entity.h"
#include "rp_stats.h"

class Enemy : public Entity, public RPStats
{
private: 
  size_t mSight{ 0 };
  bool mInBattle{ false };
  bool mDead{ false };
  
public:
  Enemy();
  void chooseAction();
  void move();
  void update();
  void setSight(size_t value);
  size_t getSight() const;
  void isDead();  
  void setBattleStatus(bool status);
  bool isInBattle() const;
};