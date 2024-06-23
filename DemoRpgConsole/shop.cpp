#include "shop.h"
#include <format>
#include <cmath>

Shop::Shop(std::shared_ptr<Npc> pNpc) :
  mpNpc{pNpc},
  mPlayer{Stats::getPlayer()},
  mInventory{Stats::getInventory()}
{
}

std::string Shop::show()
{
  std::string result;
  result.append("\t\tSHOP\n");
  result.append(mpNpc->getName() + '\n');
  result.append(std::format("{} has ${}\n", mPlayer.getName(), mPlayer.getMoney()));
  result.append(mpNpc->showStaff() + '\n');

  return result;
}

size_t Shop::getSize() const
{
  return mpNpc->getStaffSize();
}

void Shop::buy(size_t index)
{
  size_t price = mpNpc->getStaff().at(index)->getPrice();
  if (mPlayer.getMoney() >= price) {
    mInventory.add(mpNpc->getStaff().at(index));
    mpNpc->removeFromStaff(index);
    mPlayer.decreaseMoney(price);
  }
}

void Shop::sell(size_t index)
{
  size_t price = mInventory.getItem(index)->getPrice();
  mInventory.destroyItem(index);
  mPlayer.increaseMoney(static_cast<size_t>(std::floor(price * 0.25 + 0.5)));
}

std::shared_ptr<GameObject>& Shop::getItem(size_t index)
{
  return mpNpc->getStaff().at(index);
}

void Shop::destroyItem(size_t index)
{
}

Inventory& Shop::getInventory()
{
  return mInventory;
}