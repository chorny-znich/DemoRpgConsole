#include "object_manager.h"
#include "money.h"
#include "ladder.h"
#include "potion.h"
#include "weapon.h"
#include "armor.h"
#include "door.h"
#include "trap.h"
#include "arrow.h"
#include "random_placement.h"
#include "map_symbols.h"
#include "data.h" 
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <DisRealityGF.h>

/**
 * @brief create all game's objects from the specific file
 * @param filename 
*/
void ObjectManager::createObjects(const std::string& filename)
{
  mObjects.clear();
  mRandomObjects.clear();
  std::unordered_map<std::string, size_t> objects;
  ini::Document doc = ini::load(filename);
  ini::Section section = doc.getSection("general");
  objects.insert({ "money", std::stoul(section.at("Money_amount")) });
  objects.insert({"ladder", std::stoul(section.at("Ladder_amount"))});
  objects.insert({ "potion", std::stoul(section.at("Potion_amount")) });
  objects.insert({ "weapon", std::stoul(section.at("Weapon_amount")) });
  objects.insert({"armor", std::stoul(section.at("Armor_amount"))});
  objects.insert({ "door", std::stoul(section.at("Door_amount")) });
  objects.insert({ "trap", std::stoul(section.at("Trap_amount")) });
  objects.insert({ "consumable", std::stoul(section.at("Consumable_amount")) });

  // Create money objects
  for (size_t i{1}; i <= objects.at("money"); i++) {
    bool randomPosition = false;
    std::shared_ptr<Money> pMoney = std::make_shared<Money>();
    std::string sectionName = "money_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
      pMoney->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    }
    else {
      randomPosition = true;
    }
    pMoney->setVisibility(std::stoul(section.at("Visibility")));
    mObjects.push_back(std::move(pMoney));
    // Push object with the random placement
    if (randomPosition) {
      mRandomObjects.push_back(mObjects.back());
    }
  }
  // Create ladder objects
  for (size_t i{1}; i <= objects.at("ladder"); i++) {
    std::shared_ptr<Ladder> pLadder = std::make_shared<Ladder>();
    std::string sectionName = "ladder_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    pLadder->setName(section.at("Name"));
    pLadder->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    std::string ladderDirection = section.at("Direction_to");
    char symbol = ladderDirection == "UP" ? MapSymbols::LADDER_UP : MapSymbols::LADDER_DOWN;
    pLadder->setSymbol(symbol);
    pLadder->setMapIndexTo(std::stoi(section.at("Map_index_to")));
    pLadder->setPlayerSpawnTo({ std::stoi(section.at("Player_position_x")), std::stoi(section.at("Player_position_y")) });
    pLadder->setVisibility(std::stoul(section.at("Visibility")));
    mObjects.push_back(std::move(pLadder));
  }
  // Create potion objects
  for (size_t i{1}; i <= objects.at("potion"); i++) {
    bool randomPosition = false;
    std::string sectionName = "potion_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "HEALING_POTION") {
      size_t itemId = std::stoul(section.at("Id"));
      auto object = std::static_pointer_cast<HealingPotion>(Data::getItem(itemId));
      std::shared_ptr<HealingPotion> pPotion = std::make_shared<HealingPotion>();
      pPotion->setId(itemId);
      pPotion->setName(object->getName());
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pPotion->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      }
      pPotion->setPrice(object->getPrice());
      pPotion->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pPotion));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
  }
  // Create weapon objects
  for (size_t i{ 1 }; i <= objects.at("weapon"); i++) {
    bool randomPosition = false;
    std::string sectionName = "weapon_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "WEAPON") {
      size_t itemId = std::stoul(section.at("Id"));
      auto object = std::static_pointer_cast<Weapon>(Data::getItem(itemId));
      GameObjectSubType type = object->getSubType();
      std::shared_ptr<Weapon> pWeapon = std::make_shared<Weapon>(type);
      pWeapon->setId(itemId);
      pWeapon->setName(object->getName());
      pWeapon->setDamage(object->getDamage());
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pWeapon->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      } 
      pWeapon->setWeaponType(object->getWeaponType());
      pWeapon->setWeaponDistance(object->getWeaponDistance());
      pWeapon->setPrice(object->getPrice());
      pWeapon->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pWeapon));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
  }
  // Create armor objects
  for (size_t i{ 1 }; i <= objects.at("armor"); i++) {
    bool randomPosition = false;
    std::string sectionName = "armor_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "ARMOR") {
      size_t itemId = std::stoul(section.at("Id"));
      auto object = std::static_pointer_cast<Armor>(Data::getItem(itemId));
      std::shared_ptr<Armor> pArmor = std::make_shared<Armor>();
      pArmor->setId(itemId);
      pArmor->setName(object->getName());
      pArmor->setArmor(object->getArmor());
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pArmor->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      }
      pArmor->setPrice(object->getPrice());
      pArmor->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pArmor));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
  }
  // Create door objects
  for (size_t i{ 1 }; i <= objects.at("door"); i++) {
    std::string sectionName = "door_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "DOOR") {
      std::shared_ptr<Door> pDoor = std::make_shared<Door>();
      pDoor->setName(section.at("Name"));
      pDoor->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      if (section.at("Status") == "Hidden") {
        pDoor->setSymbol(MapSymbols::DOOR_HIDDEN);
        pDoor->setStatus(DoorStatus::HIDDEN);
      }
      else if (section.at("Status") == "Locked") {
        pDoor->setSymbol(MapSymbols::DOOR_LOCKED);
        pDoor->setStatus(DoorStatus::LOCKED);
      }
      else if (section.at("Status") == "Closed") {
        pDoor->setSymbol(MapSymbols::DOOR_CLOSED);
        pDoor->setStatus(DoorStatus::CLOSED);
      }
      else {
        pDoor->setSymbol(MapSymbols::DOOR_OPEN);
        pDoor->setStatus(DoorStatus::OPEN);
      }
      pDoor->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pDoor));
    }
  }
  // Create trap objects
  for (size_t i{ 1 }; i <= objects.at("trap"); i++) {
    bool randomPosition = false;
    std::shared_ptr<Trap> pTrap = std::make_shared<Trap>();
    std::string sectionName = "trap_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    pTrap->setName(section.at("Name"));
    if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
      pTrap->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    }
    else {
      randomPosition = true;
    }
    pTrap->setDamage({ std::stoul(section.at("Min_damage")), std::stoul(section.at("Max_damage")) });
    pTrap->setDifficulty(std::stoul(section.at("Difficulty")));
    pTrap->setVisibility(std::stoul(section.at("Visibility")));
    mObjects.push_back(std::move(pTrap));
    // Push object with the random placement
    if (randomPosition) {
      mRandomObjects.push_back(mObjects.back());
    }
  }
  // Create consumable objects
  for (size_t i{ 1 }; i <= objects.at("consumable"); i++) {
    bool randomPosition = false;
    std::string sectionName = "consumable_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "ARROW") {
      std::shared_ptr<Arrow> pArrow = std::make_shared<Arrow>();
      if (section.at("Position_x") != "random" && section.at("Position_y") != "random") {
        pArrow->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
      }
      else {
        randomPosition = true;
      }
      pArrow->setVisibility(std::stoul(section.at("Visibility")));
      mObjects.push_back(std::move(pArrow));
      // Push object with the random placement
      if (randomPosition) {
        mRandomObjects.push_back(mObjects.back());
      }
    }
  }
}

void ObjectManager::createRandomObjects(Map& map)
{
  RandomPlacement rp(map);
  std::vector<GameData::Position> positions = rp.place();
  auto iter = positions.begin();
  // Place objects with the random placement
  for (auto& item : mRandomObjects) {
    item->setPosition({ iter->first, iter->second });
    iter++;
  }
}

void ObjectManager::createObjects(std::vector<std::shared_ptr<GameObject>> objects)
{
  mObjects = std::move(objects);
}

const std::vector<std::shared_ptr<GameObject>>& ObjectManager::getObjects() const
{
  return mObjects;
}

std::vector<std::shared_ptr<GameObject>>& ObjectManager::getObjects()
{
  return mObjects;
}

std::shared_ptr<GameObject>& ObjectManager::getObject(GameData::Position pos)
{
  for (auto& object : mObjects) {
    if (pos.first == object->getPosition().first && pos.second == object->getPosition().second) {
      return object;
    }
  }
  throw std::runtime_error("the objects doesn't exist at this position");
}

bool ObjectManager::isObject(GameData::Position pos)
{
  for (auto object : mObjects) {
    if (object->getPosition() == pos) {
      return true;
    }
  }

  return false;
}

void ObjectManager::destroyObject(GameData::Position pos)
{
  auto iter = std::find_if(mObjects.begin(), mObjects.end(), [pos](const auto& obj) {
    return pos == obj->getPosition();
    });
  mObjects.erase(iter);
}