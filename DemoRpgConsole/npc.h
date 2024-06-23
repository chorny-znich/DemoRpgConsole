#pragma once

#include "entity.h"
#include "rp_stats.h"
#include "game_object.h"
#include <vector>
#include <memory>
#include <string>

class Npc : public Entity, public RPStats
{
private:
  std::vector<std::shared_ptr<GameObject>> mStaff;

public:
  void addStaff(std::shared_ptr<GameObject>);
  std::vector<std::shared_ptr<GameObject>>& getStaff();
  size_t getStaffSize() const;
  std::string showStaff() const;
  void removeFromStaff(size_t index);
};