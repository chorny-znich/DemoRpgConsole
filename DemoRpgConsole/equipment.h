#pragma once

#include "game_object.h"
#include <unordered_map>
#include <memory>
#include <string>

class Equipment
{
private:
  enum class EquipmentSlot {
    MELEE_WEAPON,
    RANGED_WEAPON,
    CHEST
  };
  std::unordered_map<EquipmentSlot, std::string> mSlots{
    {EquipmentSlot::MELEE_WEAPON, "Melee weapon"},
    {EquipmentSlot::RANGED_WEAPON, "Ranged weapon"},
    {EquipmentSlot::CHEST, "Chest"}
  };
  std::unordered_map<std::string, std::shared_ptr<GameObject>> mEquipment{
    {"Melee weapon", nullptr},
    {"Ranged weapon", nullptr},
    {"Chest", nullptr}
  };
  std::unordered_map<std::string, size_t> mConsumable;

public:
  void equip(std::shared_ptr<GameObject>);
  std::string show() const;
  void save();
  std::shared_ptr<GameObject> getEquipObject(const std::string& id);
  void addConsumable(const std::string& id, size_t value);
  size_t getConsumable(const std::string& id) const;
  bool hasConsumable(const std::string& id) const;
};