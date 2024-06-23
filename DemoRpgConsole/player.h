// Player
// version 1

#pragma once

#include "rp_stats.h"
#include "entity.h"
#include "game_data.h"

class Player : public RPStats, public Entity
{
private:
  const int CHAR_STEP{ 1 };
  bool mMoving{ false };
  bool mShooting{ false };
  bool mDangerStatus{ false };
  
public:
  Player();
  void update();
  void moveWest();
  void moveEast();
  void moveNorth();
  void moveSouth();
  void moving(bool move);
  bool isMoving() const;
  void shooting(bool shoot);
  bool isShooting() const;
  void setDangerStatus(bool status);
  bool getDangerStatus() const;
  bool levelupCheck();
  void levelup();
  void create();
  void save();
};