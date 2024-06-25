#include "map.h"
#include "map_symbols.h"
#include <iostream>
#include <fstream>
#include <format>
/*#include "money.h"
#include "ladder.h"
 */ 
//#include <memory>
 
Map::Map(size_t id) :
  mId{id}
{  
}

void Map::loadMap(const std::string& filename) 
{ 
  std::ifstream ifs(filename);
  if (ifs) {
    std::string line;
    while (std::getline(ifs, line)) {
      mTextMap.push_back(std::move(line));
    }
  }
  else {
    std::cerr << std::format("can't open file: {}\n\n", filename);
  }
  mMapSize = {static_cast<unsigned int>(mTextMap[0].size()), 
    static_cast<unsigned int>(mTextMap.size())};
}

void Map::createRenderMap()
{
  mRenderMap.clear();
  for (size_t y{ 0 }; y < mMapSize.y; y++) {
    std::string str{};
    for (size_t x{ 0 }; x < mMapSize.x; x++) {
      str += mLocationMap.at(y * mMapSize.x + x).getSymbol();
    }
    mRenderMap.push_back(std::move(str));
  }
}

void Map::render() {
  for (const auto& str : mRenderMap) {
    std::cout << str << '\n';
  }
  std::cout << "\n";
}

void Map::setPlayer(GameData::Position pos)
{
  mRenderMap[pos.second][pos.first] = MapSymbols::PLAYER;
  mLocationMap[pos.second * mMapSize.x + pos.first].setPlayer(true);
}

void Map::clearPlayer(GameData::Position pos)
{
  mLocationMap[pos.second * mMapSize.x + pos.first].setPlayer(false);
}

void Map::setEnemies(const std::vector<Enemy>& enemies)
{
  for (const auto enemy : enemies) {
    if (enemy.isActive()) {
      mRenderMap[enemy.getPosition().second][enemy.getPosition().first] = enemy.getSymbol();
      mLocationMap[enemy.getPosition().second * mMapSize.x + enemy.getPosition().first].setEnemy(true);
    }
    else {
      mRenderMap[enemy.getPosition().second][enemy.getPosition().first] = MapSymbols::CORPSE;
      mLocationMap[enemy.getPosition().second * mMapSize.x + enemy.getPosition().first].setEnemy(false);
    }
  }
}

void Map::clearEnemy(GameData::Position pos)
{
  mLocationMap[pos.second * mMapSize.x + pos.first].setEnemy(false);
}

void Map::setObjects(const std::vector<std::shared_ptr<GameObject>>& objects)
{
  for (const auto& object : objects) {
    if (object->isVisible()) {
      mRenderMap[object->getPosition().second][object->getPosition().first] = object->getSymbol();
      mLocationMap[object->getPosition().second * mMapSize.x + object->getPosition().first].setObject(true);
    }  
  }
}

void Map::clearObject(GameData::Position pos)
{
  mLocationMap[pos.second * mMapSize.x + pos.first].setObject(false);
}

void Map::setNpcs(const std::vector<Npc>& npcs)
{
  for (const auto& npc : npcs) {
    mRenderMap[npc.getPosition().second][npc.getPosition().first] = npc.getSymbol();
    mLocationMap[npc.getPosition().second * mMapSize.x + npc.getPosition().first].setNPC(true);
    mLocationMap[npc.getPosition().second * mMapSize.x + npc.getPosition().first].setBarrier(true);
  }
}

void Map::createMap(const std::string& filename)
{  
  loadMap(filename);
  size_t y = 0;
  for (const auto& str : mTextMap) {
    size_t x = 0;
    for (const char ch : str) {
      Location newLocation; 
      newLocation.setSymbol(ch); 
      newLocation.setPosition({ x, y });

      // check for passability
      if (ch == MapSymbols::WALL) {
        newLocation.setBarrier(true);
      }
      else if (ch == MapSymbols::DOOR_LOCKED) {
        newLocation.setBarrier(true);
      }
      mLocationMap.push_back(std::move(newLocation));
      x++;
    }
    y++;
  } 
}

GameData::LocationMap& Map::getMap()
{
  return mLocationMap;
}

sf::Vector2u Map::getMapSize() const
{
  return mMapSize;
}

Location& Map::getCurrentLocation(GameData::Position pos)
{
  return mLocationMap.at(pos.second * getMapSize().x + pos.first);
}