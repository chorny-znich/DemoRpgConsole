#pragma once

#include "game_object.h"
#include "game_data.h"

class Ladder : public GameObject
{
private:
  size_t mMapIndexTo;
  GameData::Position mPlayerSpawnTo;

public:
  Ladder();
  void setMapIndexTo(size_t index);
  size_t getMapIndexTo() const;
  void setPlayerSpawnTo(GameData::Position pos);
  GameData::Position getPlayerSpawnTo() const;
};