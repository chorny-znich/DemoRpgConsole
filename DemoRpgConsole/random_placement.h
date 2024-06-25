#pragma once
#include "map.h"
#include "object_manager.h"
#include <vector> 

/**
 * @brief Place game objects in free random places
*/
class RandomPlacement
{
private:
  Map& rmMap;
public:
  RandomPlacement(Map& map);
  RandomPlacement(const RandomPlacement&) = delete;
  RandomPlacement& operator=(const RandomPlacement&) = delete;
  std::vector<GameData::Position> place();
};