#pragma once

#include "game_data.h"
#include <memory>

class ScreenManager
{
public:
	ScreenManager() = delete;
	static void createScreen(GameData::Screens screenId);
	static void createBattleScreen(GameData::BattleType type);
};