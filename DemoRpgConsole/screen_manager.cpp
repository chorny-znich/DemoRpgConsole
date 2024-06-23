#include "screen_manager.h"
#include "menu_screen.h"
#include "explore_screen.h"
#include "player_screen.h"
#include "inventory_screen.h"
#include "shop_screen.h"
#include "battle_screen.h"
#include "hero_creation_screen.h"

#include "game_state.h"

void ScreenManager::createScreen(GameData::Screens screenID)
{ 
	if (screenID == GameData::Screens::MENU_SCREEN)
	{
		std::unique_ptr<MenuScreen> pMenuScreen = std::make_unique<MenuScreen>();
		pMenuScreen->init();
		GameState::addScreen(std::move(pMenuScreen));
	}
	
	if (screenID == GameData::Screens::EXPLORE_SCREEN)
	{
		std::unique_ptr<ExploreScreen> pExploreScreen = std::make_unique<ExploreScreen>();
		pExploreScreen->init();
		GameState::addScreen(std::move(pExploreScreen));
	}
	if (screenID == GameData::Screens::PLAYER_SCREEN)
	{
		std::unique_ptr<PlayerScreen> pPlayerScreen = std::make_unique<PlayerScreen>();
		pPlayerScreen->init();
		GameState::addScreen(std::move(pPlayerScreen));
	}
	if (screenID == GameData::Screens::INVENTORY_SCREEN)
	{
		std::unique_ptr<InventoryScreen> pInventoryScreen = std::make_unique<InventoryScreen>();
		pInventoryScreen->init();
		GameState::addScreen(std::move(pInventoryScreen));
	}
	if (screenID == GameData::Screens::SHOP_SCREEN)
	{
		std::unique_ptr<ShopScreen> pShopScreen = std::make_unique<ShopScreen>();
		pShopScreen->init();
		GameState::addScreen(std::move(pShopScreen));
	}
	if (screenID == GameData::Screens::BATTLE_SCREEN)
	{
		std::unique_ptr<BattleScreen> pBattleScreen = std::make_unique<BattleScreen>();
		pBattleScreen->init();
		GameState::addScreen(std::move(pBattleScreen));
	}
	if (screenID == GameData::Screens::HERO_CREATION_SCREEN)
	{
		std::unique_ptr<HeroCreationScreen> pHeroCreationScreen = std::make_unique<HeroCreationScreen>();
		pHeroCreationScreen->init();
		GameState::addScreen(std::move(pHeroCreationScreen));
	}
}

void ScreenManager::createBattleScreen(GameData::BattleType type)
{
	std::unique_ptr<BattleScreen> pBattleScreen = std::make_unique<BattleScreen>(type);
	pBattleScreen->init();
	GameState::addScreen(std::move(pBattleScreen));
}