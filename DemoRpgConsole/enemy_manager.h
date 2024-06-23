#pragma once

#include "enemy.h"
#include <vector>

class EnemyManager
{ 
private:
  std::vector<Enemy> mEnemies;

public:
  void createEnemies(const std::string& filename);
  void createEnemies(std::vector<Enemy> enemies);
  const std::vector<Enemy>& getEnemies() const;
  std::vector<Enemy>& getEnemies();
  Enemy& getEnemy(GameData::Position pos);
};