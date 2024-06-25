#pragma once
#include "game_data.h"
#include "location.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "game_object.h"
#include "npc.h"

class Map
{
private: 
  size_t mId;
  GameData::TextMap mTextMap;
  GameData::LocationMap mLocationMap;
  GameData::LocationMap mBeginLocationMap;
  GameData::TextMap mRenderMap;
   
  sf::Vector2u mMapSize;
  
  void loadMap(const std::string& filename);
  
public: 
  Map(size_t id);
  void createMap(const std::string& filename); 
  void createRenderMap();
  void render(); 
  GameData::LocationMap& getMap();
  GameData::LocationMap& getBeginMap();
  sf::Vector2u getMapSize() const;
  Location& getCurrentLocation(GameData::Position pos); 
  void setPlayer(GameData::Position pos); 
  void clearPlayer(GameData::Position pos);
  void setEnemies(const std::vector<Enemy>& enemies);
  void clearEnemy(GameData::Position pos);
  void setObjects(const std::vector<std::shared_ptr<GameObject>>& objects);
  void clearObject(GameData::Position pos);
  void setNpcs(const std::vector<Npc>& npcs);
};