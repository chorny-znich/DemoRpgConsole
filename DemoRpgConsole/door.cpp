#include "door.h"
#include "map_symbols.h"

Door::Door() :
  GameObject(GameObjectType::DOOR, GameObjectSubType::NONE)
{
}

void Door::setStatus(DoorStatus status)
{
  mStatus = status;
  if (mStatus == DoorStatus::CLOSED) {
    setSymbol(MapSymbols::DOOR_CLOSED);
  }
  else {
    setSymbol(MapSymbols::DOOR_OPEN);
  }
}

DoorStatus Door::getStatus() const
{
  return mStatus;
}
