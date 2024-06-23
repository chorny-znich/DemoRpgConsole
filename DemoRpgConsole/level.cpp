#include "level.h"
#include <format>

void Level::init()
{
  for (size_t i = 0; i < NUMBER_OF_MAPS; i++) {
    Map newMap(i);
    newMap.createMap(std::format("data/maps/map_{}.txt", i));
    mMaps.insert({i, newMap });

    mEnemyList.insert({ i, std::format("data/enemies/enemies_{}.txt", i)});
    mObjectList.insert({ i, std::format("data/objects/objects_{}.txt", i) });
    mNPCList.insert({ i, std::format("data/npc/npc_{}.txt", i) });
  }
}

Map& Level::getCurrentMap()
{
  return mMaps.at(mCurrentMapIndex);
}

const std::string& Level::getCurrentEnemyListFilename() const
{
  return mEnemyList.at(mCurrentMapIndex);
}

const std::string& Level::getCurrentObjectListFilename() const
{
  return mObjectList.at(mCurrentMapIndex);
}

const std::string& Level::getCurrentNPCListFilename() const
{
  return mNPCList.at(mCurrentMapIndex);
}

void Level::setPlayerSpawnPosition(GameData::Position pos)
{
  mPlayerSpawnPosition = pos;
}

GameData::Position Level::getPlayerSpawnPosition()
{
  return mPlayerSpawnPosition;
}

void Level::setCurrentMapIndex(size_t index) {
  mCurrentMapIndex = index;
}