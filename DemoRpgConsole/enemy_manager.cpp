#include "enemy_manager.h"
#include "data.h"
#include <DisRealityGF.h>

void EnemyManager::createEnemies(const std::string& filename)
{
  mEnemies.clear();
  size_t enemiesAmount{ 0 };
  ini::Document doc = ini::load(filename);
  ini::Section section = doc.getSection("general");
  enemiesAmount = std::stoul(section.at("Enemies_amount"));
  
  for (size_t i{ 1 }; i <= enemiesAmount; i++) {
    std::string sectionName = "enemy_" + std::to_string(i);
    ini::Section section = doc.getSection(sectionName);
    size_t id = std::stoul(section.at("Id"));
    Enemy enemy;
    Enemy& enemyRef{Data::getEnemy(id)};
    enemy.spawn({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y"))});
    enemy.setSymbol(enemyRef.getSymbol());
    enemy.setName(enemyRef.getName());
    enemy.setExperienceForKill(enemyRef.getExperienceForKill());
    enemy.setMaxHealth(enemyRef.getHealth());
    enemy.setSecondaryStatValue("Attack", enemyRef.getSecondaryStatValue("Attack"));
    enemy.setSecondaryStatValue("Defence", enemyRef.getSecondaryStatValue("Defence"));
    enemy.setHealth(enemyRef.getHealth());
    enemy.setDamage(enemyRef.getDamage());
    enemy.setSight(enemyRef.getSight());
    mEnemies.push_back(std::move(enemy));
  }
}

void EnemyManager::createEnemies(std::vector<Enemy> enemies)
{
  mEnemies = std::move(enemies);
}

const std::vector<Enemy>& EnemyManager::getEnemies() const
{
    return mEnemies;
}

std::vector<Enemy>& EnemyManager::getEnemies()
{
  return mEnemies;
}

Enemy& EnemyManager::getEnemy(GameData::Position pos)
{
  for (auto& enemy : mEnemies) {
    if (pos.first == enemy.getPosition().first && pos.second == enemy.getPosition().second) {
      return enemy;
    }
  }
  throw std::runtime_error("Enemy don't exist");    
}