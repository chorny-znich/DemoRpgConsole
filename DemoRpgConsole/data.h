#pragma once

#include <unordered_map>
#include "game_object.h"
#include "potion.h"
#include "weapon.h"
#include "armor.h"
#include "enemy.h"
#include <DisRealityGF.h>
#include <memory>

class Data
{
private:
  static Data* mpInstance;
  std::unordered_map<size_t, std::shared_ptr<GameObject>> mItemDatabase;
  std::unordered_map<size_t, Enemy> mEnemyDatabase;
  std::unordered_map<size_t, Potion> mPotionDatabase;
  std::unordered_map<size_t, Weapon> mWeaponDatabase;
  std::unordered_map<size_t, Armor> mArmorDatabase;

public:
  Data();
  void init();
  static std::shared_ptr<GameObject> getItem(size_t id);
  static Enemy& getEnemy(size_t id);
};