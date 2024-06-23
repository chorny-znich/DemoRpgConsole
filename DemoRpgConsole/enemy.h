#pragma once

#include "entity.h"
#include "rp_stats.h"

class Enemy : public Entity, public RPStats
{
private: 
  bool mInBattle{ false };
  bool mDead{ false };
  
public:
  Enemy();
  void move();
  void update();
  void isDead();  
  void setBattleStatus(bool status);
  bool isInBattle() const;
};