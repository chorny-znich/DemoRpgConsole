#include "equipment.h"
#include "game_object_type.h"
#include <format>
#include <iostream>
#include <fstream>

void Equipment::equip(std::shared_ptr<GameObject> pObject)
{
  if (pObject->getType() == GameObjectType::WEAPON && pObject->getSubType() == GameObjectSubType::MELEE) {
    mEquipment["Melee weapon"] = pObject;
  }
  if (pObject->getType() == GameObjectType::WEAPON && pObject->getSubType() == GameObjectSubType::RANGED) {
    mEquipment["Ranged weapon"] = pObject;
  }
  if (pObject->getType() == GameObjectType::ARMOR && pObject->getSubType() == GameObjectSubType::CHEST) {
    mEquipment["Chest"] = pObject;
  }
}

std::string Equipment::show() const
{
  std::string result{};
  result.append("EQUIPMENT:\n");
  for (auto [first, second] : mEquipment) {
    if (second != nullptr) {
      result.append(std::format("{} - {}\n", first, second->getName()));
    }
    else {
      result.append(std::format("{} -\n", first));
    }
  }
  result.append("\nCONSUMABLE:\n");
  for (auto& [first, second] : mConsumable) {
    result.append(std::format("{} - {}\n", first, second));
  }
  result.append("\n\n");
  return result;
}

void Equipment::save()
{
  std::ofstream ofs(GameData::path::Save, std::ios::app);
  if (ofs) {
    ofs << "\n[Equipment]\n";
    for (const auto& item : mEquipment) {
      if (item.second != nullptr) {
        ofs << item.first << "=" << item.second->getId() << "\n";
      }
    }
  }
  else {
    std::cout << "\nCan't create a save file\n";
  }
}

std::shared_ptr<GameObject> Equipment::getEquipObject(const std::string& id)
{
    return mEquipment.at(id);
}

void Equipment::addConsumable(const std::string& id, size_t value)
{
  mConsumable.insert({ id, value });
}

void Equipment::increaseConsumable(const std::string& id, size_t value)
{
  mConsumable[id] += value;
}

void Equipment::decreaseConsumable(const std::string& id, size_t value)
{
  mConsumable[id] -= value;
}

size_t Equipment::getConsumable(const std::string& id) const
{
  auto iter = mConsumable.find(id);
  return iter->second;
}

bool Equipment::hasConsumable(const std::string& id) const
{
  return mConsumable.find(id) != mConsumable.end() ? true : false;
}