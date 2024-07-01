#include "entity.h"

void Entity::spawn(GameData::Position pos) 
{
  mPosition = pos;
}

void Entity::setActiveStatus(bool status)
{
  mActive = status;
}

bool Entity::isActive() const
{
  return mActive;
}

GameData::Position Entity::getPosition() const
{
  return mPosition;
}

GameData::Movement Entity::getMovement() const
{
  return mMovement;
}

void Entity::setSymbol(char ch)
{
  mSymbol = ch;
}

char Entity::getSymbol() const
{
  return mSymbol;
}

void Entity::checkEnvironment(std::map<GameData::Direction, Location*>& locations)
{
  mEntityEnvironment[GameData::Direction::NORTH] =std::move(locations[GameData::Direction::NORTH]);
  mEntityEnvironment[GameData::Direction::EAST] = std::move(locations[GameData::Direction::EAST]);
  mEntityEnvironment[GameData::Direction::SOUTH] =std::move(locations[GameData::Direction::SOUTH]);
  mEntityEnvironment[GameData::Direction::WEST] = std::move(locations[GameData::Direction::WEST]);
}