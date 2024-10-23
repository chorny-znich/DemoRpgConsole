#include "game_object.h"

GameObject::GameObject(GameObjectType type, GameObjectSubType subType) :
  mSymbol{},
  mType{ type },
  mSubType{subType},
  mPrice{0},
  mVisible{false},
  mVisibility{0},
  mAmount{0}
{
}

void GameObject::setId(size_t id)
{
  mId = id;
}

size_t GameObject::getId() const
{
  return mId;
}

void GameObject::setType(GameObjectType type)
{
  mType = type;
}

GameObjectType GameObject::getType() const
{
    return mType;
}

void GameObject::setSubType(GameObjectSubType subType)
{
  mSubType = subType;
}

GameObjectSubType GameObject::getSubType() const
{
  return mSubType;
}

void GameObject::setName(const std::string& name)
{
  mName = name;
}

std::string GameObject::getName() const
{
  return mName;
}

void GameObject::setPosition(GameData::Position pos)
{
  mPosition = pos;
}

GameData::Position GameObject::getPosition() const
{
  return mPosition;
}

void GameObject::setSymbol(char symbol)
{
  mSymbol = symbol;
}

char GameObject::getSymbol() const
{
  return mSymbol;
}

void GameObject::setPrice(size_t value)
{
  mPrice = value;
}

size_t GameObject::getPrice() const
{
  return mPrice;
}

void GameObject::setVisibleStatus(bool value)
{
  mVisible = value;
}

bool GameObject::isVisible() const
{
  return mVisible;
}

void GameObject::setVisibility(size_t value)
{
  mVisibility = value;
}

size_t GameObject::getVisibility() const
{
  return mVisibility;
}

void GameObject::setAmount(size_t value)
{
  mAmount = value;
}

size_t GameObject::getAmount() const
{
  return mAmount;
}
