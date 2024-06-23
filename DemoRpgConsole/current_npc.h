#pragma once

#include "npc.h"
#include <memory>

class CurrentNpc
{
  std::shared_ptr<Npc> mpNpc{ nullptr };
  static inline CurrentNpc* mpInstance{ nullptr };

public:
  CurrentNpc();
  static void setNpc(std::shared_ptr<Npc> pNpc);
  static std::shared_ptr<Npc> getNpc();
  
};

