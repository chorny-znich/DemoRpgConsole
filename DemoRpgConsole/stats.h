// Player's statistics, inventory and equipment for using by other classes
// version 1

#pragma once

#include "player.h"
#include "inventory.h"
#include "equipment.h"
#include <memory>

class Stats
{
private:
  Player& mPlayer;
  Inventory& mInventory;
  Equipment& mEquipment;
  static inline Stats* mpInstance{ nullptr };

public:
  Stats(Player& player, Inventory& inventory, Equipment& equipment);
  static Player& getPlayer();
  static Inventory& getInventory();
  static Equipment& getEquipment();
};