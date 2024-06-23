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