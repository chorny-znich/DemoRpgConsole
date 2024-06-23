#include "level_manager.h"

void LevelManager::setVisited()
{
  mVisitedMaps[mCurrentMapIndex] = true;
}

bool LevelManager::isVisited() const
{
  return mVisitedMaps.find(mCurrentMapIndex) != mVisitedMaps.end() ? true : false;
}

void LevelManager::saveCurrentState(std::vector<Enemy>& enemies,
  std::vector<std::shared_ptr<GameObject>> objects, std::vector<Npc>& npc)
{
  mEnemies[mCurrentMapIndex] = std::move(enemies);
  mObjects[mCurrentMapIndex] = std::move(objects);
  mNpc[mCurrentMapIndex] = std::move(npc);
}
 
std::vector<Enemy> LevelManager::loadEnemies()
{
  return mEnemies.at(mCurrentMapIndex);
}

std::vector<std::shared_ptr<GameObject>> LevelManager::loadObjects()
{
  return mObjects.at(mCurrentMapIndex);
}

std::vector<Npc>& LevelManager::loadNpc()
{
  return mNpc.at(mCurrentMapIndex);
}

void LevelManager::setCurrentMapIndex(size_t index)
{
  mCurrentMapIndex = index;
}
