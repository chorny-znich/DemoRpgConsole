#include "data.h"
#include "game_data.h"
#include <cassert>

Data* Data::mpInstance{ nullptr };

Data::Data()
{
  assert(mpInstance == nullptr);
  mpInstance = this;
}

void Data::init()
{
  std::unordered_map<std::string, size_t> items;
  ini::Document doc = ini::load(GameData::path::ItemsInfo);
  ini::Section section = doc.getSection("general");
  items.insert({ "potion", std::stoul(section.at("Potion_amount")) });
  items.insert({ "weapon", std::stoul(section.at("Weapon_amount")) });
  items.insert({ "armor", std::stoul(section.at("Armor_amount")) });
  
  // Create potion objects
  for (size_t i{ 1 }; i <= items.at("potion"); i++) {
    std::string sectionName = "potion_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "HEALING_POTION") {
      std::shared_ptr<HealingPotion> pPotion = std::make_shared<HealingPotion>();
      pPotion->setName(section.at("Name"));
      pPotion->setPrice(std::stoul(section.at("Price")));
      //mPotionDatabase.insert({i, std::move(pPotion) });
      mItemDatabase.insert({ std::stoul(section.at("Id")), std::move(pPotion)});
    }
  }
  // Create weapon objects
  for (size_t i{ 1 }; i <= items.at("weapon"); i++) {
    std::string sectionName = "weapon_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "WEAPON") {
      std::shared_ptr<Weapon> pWeapon;
      if (section.at("Weapon_type") == "MELEE") {
        pWeapon = std::make_shared<Weapon>(GameObjectSubType::MELEE);
      }
      else {
        pWeapon = std::make_shared<Weapon>(GameObjectSubType::RANGED);
      }
      pWeapon->setName(section.at("Name"));
      pWeapon->setDamage({ std::stoul(section.at("Damage_min")), std::stoul(section.at("Damage_max")) });
      pWeapon->setPrice(std::stoul(section.at("Price")));
      pWeapon->setWeaponType(section.at("Weapon_type") == "MELEE" ? WeaponType::MELEE : WeaponType::RANGED);
      pWeapon->setWeaponDistance(std::stoul(section.at("Distance")));
      //mWeaponDatabase.insert({ i, std::move(pWeapon) });
      mItemDatabase.insert({ std::stoul(section.at("Id")), std::move(pWeapon) });
    }
  }
  // Create armor objects
  for (size_t i{ 1 }; i <= items.at("armor"); i++) {
    std::string sectionName = "armor_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    if (section.at("Type") == "ARMOR") {
      std::shared_ptr<Armor> pArmor = std::make_shared<Armor>();
      pArmor->setName(section.at("Name"));
      pArmor->setPrice(std::stoul(section.at("Price")));
      pArmor->setArmor(std::stoul(section.at("Armor")));
      //mArmorDatabase.insert({ i, std::move(pArmor) });
      mItemDatabase.insert({ std::stoul(section.at("Id")), std::move(pArmor) });
    }
  }
  // Create enemy list
  doc = ini::load(GameData::path::EnemiesInfo);
  section = doc.getSection("general");
  size_t enemyAmount = std::stoul(section.at("Enemies_amount"));

  for (size_t i{ 1 }; i <= enemyAmount; i++) {
    std::string sectionName = "enemy_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    Enemy enemy;
    enemy.setSymbol(section.at("Symbol")[0]);
    enemy.setName(section.at("Name"));
    enemy.setExperienceForKill(std::stoi(section.at("Experience_for_kill")));
    enemy.setMaxHealth(std::stoi(section.at("Health")));
    enemy.setSecondaryStatValue("Attack", std::stoul(section.at("Attack")));
    enemy.setSecondaryStatValue("Defence", std::stoul(section.at("Defence")));
    enemy.setHealth(std::stoul(section.at("Health")));
    enemy.setDamage({ std::stoul(section.at("Damage_min")), std::stoul(section.at("Damage_max")) });
    mEnemyDatabase.insert({ i, std::move(enemy) });
  }
}

std::shared_ptr<GameObject> Data::getItem(size_t id)
{
  auto& itemDatabase = mpInstance->mItemDatabase;
  return itemDatabase.at(id);
}

Enemy& Data::getEnemy(size_t id)
{
  auto& enemyDatabase = mpInstance->mEnemyDatabase;
  return enemyDatabase.at(id);
}