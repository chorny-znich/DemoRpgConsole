#include "location.h"

void Location::setPosition(Position pos)
{
  mPosition = pos;
}

Position Location::getPosition() const
{
  return mPosition;
}

void Location::setSymbol(char ch)
{
  mSymbol = ch;
}

char Location::getSymbol() const
{
  return mSymbol;
}

void Location::setBarrier(bool value)
{
  mBarrier = value;
}

bool Location::isBarrier() const
{
  return mBarrier;
}

void Location::setPlayer(bool value)
{
  mPlayer = value;
}

bool Location::isPlayer() const
{
  return mPlayer;
}

void Location::setEnemy(bool value)
{
  mEnemy = value;
}

bool Location::isEnemy() const
{
    return mEnemy;
} 
void Location::setObject(bool value)
{
  mObject = value;
}
bool Location::isObject() const
{
  return mObject;
}

void Location::setNPC(bool value)
{
  mNpc = value;
}

bool Location::isNpc() const
{
    return mNpc;
}
