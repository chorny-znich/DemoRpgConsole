#include "random_placement.h"
#include <algorithm>
#include <random>

RandomPlacement::RandomPlacement(Map& map) :
  rmMap{map}
{
}

std::vector<GameData::Position> RandomPlacement::place()
{
  std::vector<GameData::Position> result;
  GameData::LocationMap& map = rmMap.getBeginMap();
  for (const auto& item : map) {
    if (!item.isBarrier() && !item.isEnemy() && !item.isNpc() && !item.isObject() && !item.isPlayer()) {
      result.push_back(item.getPosition());
    }
  }
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::shuffle(result.begin(), result.end(), gen);
  return result;
}