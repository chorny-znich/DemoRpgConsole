#include "inventory.h"
#include "game_object_type.h"
#include <format>
#include <fstream>
#include <iostream>

void Inventory::add(std::shared_ptr<GameObject> pObject)
{
  mInventory.push_back(std::move(pObject));
}

std::string Inventory::show()
{
  std::string result{};
  result.append("INVENTORY:\n");
  if (mInventory.size() == 0) {
    return result.append("Inventory is empty");
  }
  size_t counter{ 1 };
  for (auto pObject : mInventory) {
    result.append(std::format("{}. {}\n", counter++, pObject->getName()));
  }

  return result;
}

size_t Inventory::getSize() const
{
    return mInventory.size();
}

std::shared_ptr<GameObject>& Inventory::getItem(size_t index)
{
  return mInventory.at(index);
}

void Inventory::destroyItem(size_t index)
{
  mInventory.erase(mInventory.begin() + index);
}

void Inventory::save()
{
  std::ofstream ofs(GameData::path::Save, std::ios::app);
  if (ofs) {
    ofs << "\n[Inventory]\n";
    for (const auto& item : mInventory) {
        ofs << item->getId() << "\n";
    }
  }
  else {
    std::cout << "\nCan't create a save file\n";
  }
}