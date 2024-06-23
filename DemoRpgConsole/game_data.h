#pragma once

#include "location.h"
#include <vector>
#include <string>
#include <SFML/System.hpp>

namespace GameData { 
  using TextMap = std::vector<std::string>;
  using LocationMap = std::vector<Location>; 
  using Position = std::pair<size_t, size_t>;
  using Movement = std::pair<int, int>;

  const sf::Vector2u DICE{ 1, 12 };

  enum class Screens {
    MENU_SCREEN,
    EXPLORE_SCREEN,
    PLAYER_SCREEN,
    INVENTORY_SCREEN,
    SHOP_SCREEN,
    BATTLE_SCREEN,
    HERO_CREATION_SCREEN
  };

  inline namespace path {
    const std::string PlayerInfo = R"(data/player.txt)";
    const std::string ItemsInfo = R"(data/items.txt)";
    const std::string EnemiesInfo = R"(data/enemy_list.txt)";
    const std::string Save = R"(data/save/save.txt)";
  }
  
  const char UI_DIVIDER_SYMBOL = '=';
  const size_t UI_DIVIDER_WIDTH = 30;
  
  enum class BattleType {
    MELEE,
    RANGED
  };
  enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
  };
}