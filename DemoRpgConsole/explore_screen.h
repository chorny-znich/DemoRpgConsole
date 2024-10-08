#pragma once

#include "screen.h"
#include "map.h"
#include "player.h"
#include "inventory.h"
#include "equipment.h"
#include "enemy_manager.h"
#include "object_manager.h"
#include "npc_manager.h"
#include "console_ui.h"
#include "level.h"
#include "level_manager.h"
#include "stats.h"
#include "battle_action.h"
#include "current_npc.h"
#include "game_data.h"
#include "CurrentMapData.h"
#include <map>

class ExploreScreen : public Screen
{	
private:
	enum class Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST,
		NONE
	};
	std::map<size_t, Direction> mDirection{
		{1, Direction::NORTH},
		{2, Direction::EAST},
		{3, Direction::SOUTH},
		{4, Direction::WEST}
	};
	std::map<size_t, std::string> mDirectionString{
		{1, "North"},
		{2, "East"},
		{3, "South"},
		{4, "West"}
	};
	std::map<Direction, Location*> mHeroEnvironment{
		{Direction::NORTH, nullptr},
		{Direction::EAST, nullptr},
		{Direction::SOUTH, nullptr},
		{Direction::WEST, nullptr}
	};
	enum class Action {
		SHOOT_NORTH,
		SHOOT_EAST,
		SHOOT_SOUTH,
		SHOOT_WEST,
		DISARM_TRAP,
		NONE
	};
	Action mAction;

	std::map<Action, std::string> mActionList{
		{Action::SHOOT_NORTH, "Shoot north"},
		{Action::SHOOT_EAST, "Shoot east"},
		{Action::SHOOT_SOUTH, "Shoot south"},
		{Action::SHOOT_WEST, "Shoot west"},
		{Action::DISARM_TRAP, "Disarm trap"}
	};
	std::map<size_t, std::pair<Direction, Action>> mHeroAction;

	enum class GameplayState 
	{
		START,
		PLAYER_INPUT,
		PLAYER_TURN,
		PLAYER_ATTACK,
		PLAYER_ACT,
		PLAYER_TURN_SHOW,
		ENEMY_TURN,
		ENEMY_TURN_SHOW
	};
	GameplayState mState{ GameplayState::START };
	
	Player mPlayer;
	Inventory mInventory;
	Equipment mEquipment;
	EnemyManager mEnemyManager;
	ObjectManager mObjectManager;
	NpcManager mNpcManager;
	ConsoleUI mConsoleUI;
	Level mLevel;
	LevelManager mLevelManager;
	Map mCurrentMap;
	Stats mStats;
	BattleAction mBattleAction;
	CurrentNpc mCurrentNpc;
	CurrentMapData mCurrentMapData;
	 
	bool collisionDetection(GameData::Position pos, GameData::Movement move);
	bool battleDetection(GameData::Position pos, GameData::Movement move);
	void pickItem();
	void useLadder();
	void checkDoors(GameData::Position pos);
	void useDoor(std::shared_ptr<GameObject> pObject);
	void showStats(Player& player);
	void showInventory();
	bool checkNpcNearby(GameData::Position pos);
	void showShop();
	void showBattle();
	std::string showLocationInfo();
	void changeMap();
	void checkEnvironment(GameData::Position pos);
	void checkHeroEnvironment(GameData::Position pos);
	bool checkVisibility(size_t value);
	void saveGame();
	void shoot(GameData::Direction direction);
	bool fellTrap();
	bool disarmTrap(GameData::Position pos);

public:
	ExploreScreen();

	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};