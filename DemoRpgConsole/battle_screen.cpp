#include "battle_screen.h"
#include "console_ui.h"
#include "game_state.h"
#include "battle_action.h"
#include "ranged_battle.h"
#include <conio.h>
#include <iostream>
#include <format>

BattleScreen::BattleScreen(GameData::BattleType type) :
  mBattleType{type}
{
}

void BattleScreen::init()
{
  if (mBattleType == GameData::BattleType::RANGED) {
    mConsoleUI.addCommand("Shoot North");
    mConsoleUI.addCommand("Shoot East");
    mConsoleUI.addCommand("Shoot South");
    mConsoleUI.addCommand("Shoot West");
  }
  else {
    mConsoleUI.addCommand("Attack");
    if (BattleAction::getPlayer().getSecondaryStatValue("Attack") >= STRONG_ATTACK_MODIFIER) {
      mConsoleUI.addCommand("Strong attack");
    }
  }
}

void BattleScreen::inputHandler()
{
  if (_kbhit()) {
    char menuItem = _getch();
    if (mBattleType == GameData::BattleType::MELEE) {
      switch (menuItem) {
      case 49:
        BattleAction::setAction(BattleActions::ATTACK);
        break;
      case 50:
        if (BattleAction::getPlayer().getSecondaryStatValue("Attack") >= STRONG_ATTACK_MODIFIER) {
          BattleAction::setAction(BattleActions::STRONG_ATTACK);
        }
        break;
      }
      GameState::destroyScreen();
    }
    if (mBattleType == GameData::BattleType::RANGED) {
      RangedBattle rangedBattle;
      switch (menuItem) {
      case '1':
        rangedBattle.shoot(GameData::Direction::NORTH);
        break;
      case '2':
        rangedBattle.shoot(GameData::Direction::EAST);
        break;
      case '3':
        rangedBattle.shoot(GameData::Direction::SOUTH);
        break;
      case '4':
        rangedBattle.shoot(GameData::Direction::WEST);
        break;
      }
      std::string s;
      std::cin >> s;
      system("cls");
      GameState::destroyScreen();
    }
  }
}

void BattleScreen::update()
{
}

void BattleScreen::render()
{
  mConsoleUI.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
  if (mBattleType == GameData::BattleType::MELEE) {
    std::cout << std::format("You attack {}\n", BattleAction::getCurrentEnemy()->getName());
    std::cout << std::format("HP: {}\n", BattleAction::getCurrentEnemy()->getHealth());
  }
  if (mBattleType == GameData::BattleType::RANGED) {
    std::cout << std::format("Which direction do you want to shoot?\n");
  }
  mConsoleUI.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
  mConsoleUI.displayCommandString();
}