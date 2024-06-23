#include "CurrentMapData.h"
#include <cassert>

CurrentMapData::CurrentMapData(Player& player, Inventory& inventory, Equipment& equipment) :
  mPlayer{ player },
  mInventory{ inventory },
  mEquipment{ equipment },
  mpEnemies{nullptr},
  mpMap{nullptr}
{
  assert(mpInstance == nullptr);
  mpInstance = this;
}

void CurrentMapData::changeMap(std::vector<Enemy>* enemies, GameData::LocationMap* map, sf::Vector2u mapSize)
{
  mpEnemies = std::move(enemies);
  mpMap = std::move(map);
  mMapSize = std::move(mapSize);
}

Player& CurrentMapData::getPlayer()
{
  auto& player = mpInstance->mPlayer;
  return player;
}

Inventory& CurrentMapData::getInventory()
{
  auto& inventory = mpInstance->mInventory;
  return inventory;
}

Equipment& CurrentMapData::getEquipment()
{
  auto& equipment = mpInstance->mEquipment;
  return equipment;
}

std::vector<Enemy>& CurrentMapData::getEnemies()
{
  auto& enemies = mpInstance->mpEnemies;
  return *enemies;
}

GameData::LocationMap& CurrentMapData::getMap()
{
  auto& map = mpInstance->mpMap;
  return *map;
}

sf::Vector2u CurrentMapData::getMapSize()
{
  auto& mapSize = mpInstance->mMapSize;
  return mapSize;
}
