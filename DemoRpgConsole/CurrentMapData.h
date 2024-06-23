#pragma once
#include "player.h"
#include "inventory.h"
#include "equipment.h"
#include "map.h"
#include "enemy.h"
#include "game_data.h"
#include <memory>
#include <SFML/Graphics.hpp>

/**
 * @brief References and pointers to all the current map data
*/
class CurrentMapData
{
private:
  Player& mPlayer;
  Inventory& mInventory;
  Equipment& mEquipment;
  std::vector<Enemy>* mpEnemies;
  GameData::LocationMap* mpMap;
  sf::Vector2u mMapSize;

  static inline CurrentMapData* mpInstance{ nullptr };
public:
  CurrentMapData(Player& player, Inventory& inventory, Equipment& equipment);

  void changeMap(std::vector<Enemy>* enemies, GameData::LocationMap* map, sf::Vector2u mapSize);

  static Player& getPlayer();
  static Inventory& getInventory();
  static Equipment& getEquipment();
  static std::vector<Enemy>& getEnemies();
  static GameData::LocationMap& getMap();
  static sf::Vector2u getMapSize();
};

