#pragma once

#include "game_data.h"
#include "location.h"
#include <vector>
#include <map>

/**
 * @brief A base class for all entities
*/
class Entity
{ 
private:
  bool mActive{ true };

protected:
  GameData::Position mPosition;
  GameData::Movement mMovement{ 0, 0 };
  char mSymbol;
  
  std::map<GameData::Direction, std::vector<Location*>> mEntityEnvironment{
    {GameData::Direction::NORTH, {}},
    {GameData::Direction::EAST, {}},
    {GameData::Direction::SOUTH, {}},
    {GameData::Direction::WEST, {}}
  };
  
public:
  void spawn(GameData::Position pos);
  void setActiveStatus(bool status);
  bool isActive() const;
  GameData::Position getPosition() const;
  GameData::Movement getMovement() const;
  void setSymbol(char ch);
  char getSymbol() const; 

  void checkEnvironment(std::map<GameData::Direction, std::vector<Location*>>& locations);
};