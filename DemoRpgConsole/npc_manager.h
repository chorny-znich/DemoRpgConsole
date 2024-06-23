#pragma once

#include "npc.h"
#include <vector>

class NpcManager
{
private:
  std::vector<Npc> mNpc;

public:
  void createNpcs(const std::string& filename);
  void createNpcs(std::vector<Npc>& npc);
  const std::vector<Npc>& getNpcs() const;
  std::vector<Npc>& getNpcs();
  Npc& getNpc(GameData::Position pos);
};