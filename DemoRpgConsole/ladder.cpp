#include "ladder.h"

Ladder::Ladder() :
  GameObject(GameObjectType::LADDER, GameObjectSubType::NONE)
{
}

void Ladder::setMapIndexTo(size_t index)
{
  mMapIndexTo = index;
}

size_t Ladder::getMapIndexTo() const
{
  return mMapIndexTo;
}

void Ladder::setPlayerSpawnTo(GameData::Position pos)
{
  mPlayerSpawnTo = pos;
}

GameData::Position Ladder::getPlayerSpawnTo() const
{
  return mPlayerSpawnTo;
}