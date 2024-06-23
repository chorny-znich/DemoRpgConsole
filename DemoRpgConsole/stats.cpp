#include "stats.h"
#include <assert.h>

Stats::Stats(Player& player, Inventory& inventory, Equipment& equipment) :
  mPlayer{player},
  mInventory{inventory},
  mEquipment{ equipment }
{
  assert(mpInstance == nullptr);
  mpInstance = this;
}

Player& Stats::getPlayer()
{
  auto& player = mpInstance->mPlayer;
  return player;
}

Inventory& Stats::getInventory()
{
  auto& inventory = mpInstance->mInventory;
  return inventory;
}

Equipment& Stats::getEquipment()
{
  auto& equipment = mpInstance->mEquipment;
  return equipment;
}
