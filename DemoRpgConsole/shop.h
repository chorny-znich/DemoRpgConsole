#pragma once

#include "game_object.h"
#include "npc.h"
#include "stats.h"
#include <vector>
#include <memory>

class Shop
{
private:
  std::shared_ptr<Npc> mpNpc;
  Player& mPlayer;
  Inventory& mInventory;

public:
  Shop(std::shared_ptr<Npc> pNpc);
  std::string show();
  size_t getSize() const;
  void buy(size_t index);
  void sell(size_t index);
  std::shared_ptr<GameObject>& getItem(size_t index);
  void destroyItem(size_t index);
  Inventory& getInventory();
};