// Manage game maps
// Save the currunt map when the player leaves it
// Load a map that a player have been visited already
 
#pragma once
#include "level.h"
#include "enemy.h"
#include "game_object.h"
#include <map>

class LevelManager
{
private:
  size_t mCurrentMapIndex{ 0 };
  std::map <size_t, bool> mVisitedMaps;
  std::map<size_t, std::vector<Enemy>> mEnemies;
  std::map<size_t, std::vector<std::shared_ptr<GameObject>>> mObjects;
  std::map<size_t, std::vector<Npc>> mNpc;
public:
  void setVisited();
  bool isVisited() const;
  void saveCurrentState(std::vector<Enemy>& enemies, 
    std::vector<std::shared_ptr<GameObject>> objects, std::vector<Npc>& npc);
  std::vector<Enemy> loadEnemies();
  std::vector<std::shared_ptr<GameObject>> loadObjects();
  std::vector<Npc>& loadNpc();
  void setCurrentMapIndex(size_t index);
};