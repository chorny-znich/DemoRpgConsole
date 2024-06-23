#include "door.h"
#include "map_symbols.h"

Door::Door() :
  GameObject(GameObjectType::DOOR, GameObjectSubType::NONE)
{
}

void Door::setStatus(DoorStatus status)
{
  mStatus = status;
  if (mStatus == DoorStatus::LOCKED) {
    setSymbol(MapSymbols::DOOR_LOCKED);
  }
  else {
    setSymbol(MapSymbols::DOOR_UNLOCKED);
  }
}

DoorStatus Door::getStatus() const
{
  return mStatus;
}
