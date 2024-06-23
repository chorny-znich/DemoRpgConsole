// Base class for all entities
// version 1

#pragma once

#include "game_data.h"

class Entity
{ 
private:
  bool mActive{ true };

protected:
  GameData::Position mPosition;
  GameData::Movement mMovement{ 0, 0 };
  char mSymbol;

public:
  void spawn(GameData::Position pos);
  void setActiveStatus(bool status);
  bool isActive() const;
  GameData::Position getPosition() const;
  GameData::Movement getMovement() const;
  void setSymbol(char ch);
  char getSymbol() const; 
};