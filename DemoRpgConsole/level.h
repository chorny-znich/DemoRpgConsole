#pragma once

#include <string>
#include <unordered_map> 
#include "map.h"
#include "game_data.h"

class Level
{
private:
  const size_t NUMBER_OF_MAPS = 7;
  size_t mCurrentMapIndex{ 0 };
  std::unordered_map<size_t, Map> mMaps;
  std::unordered_map<size_t, std::string> mEnemyList;
  std::unordered_map<size_t, std::string> mObjectList; 
  std::unordered_map<size_t, std::string> mNPCList;
  GameData::Position mPlayerSpawnPosition{1, 1};

public:
  void init();
  Map& getCurrentMap();
  const std::string& getCurrentEnemyListFilename() const;
  const std::string& getCurrentObjectListFilename() const;
  const std::string& getCurrentNPCListFilename() const;
  void setPlayerSpawnPosition(GameData::Position);
  GameData::Position getPlayerSpawnPosition();
  void setCurrentMapIndex(size_t index);
};