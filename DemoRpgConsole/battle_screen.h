#pragma once
#include "screen.h"
#include "console_ui.h"
#include "game_data.h"

class BattleScreen : public Screen
{
private:
  ConsoleUI mConsoleUI;
  GameData::BattleType mBattleType{ GameData::BattleType::MELEE };

public:
  BattleScreen() = default;
  BattleScreen(GameData::BattleType type);
  void init();
  void inputHandler();
  void update();
  void render();
};