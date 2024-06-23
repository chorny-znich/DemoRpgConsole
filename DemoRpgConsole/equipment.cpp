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
