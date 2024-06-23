#include "player_screen.h"
#include "player.h"
#include "game_state.h"
#include "stats.h"
#include <iostream>
#include <format>
#include <conio.h>

PlayerScreen::PlayerScreen() :
  mState{ States::SHOW_STATS },
  mPlayer{Stats::getPlayer()},
  mRenderScreen{true}
{
}

void PlayerScreen::showStats()
{
  std::cout << std::format("\tName: {}\n", mPlayer.getName());
  std::cout << std::format("Lvl:{}\tExp:{}\t${}\n", mPlayer.getLevel(), mPlayer.getExperience(), mPlayer.getMoney());
  std::cout << std::format("HP:{}/{}\n", mPlayer.getHealth(), mPlayer.getMaxHealth());
  std::cout << std::format("Armor:{}\n", mPlayer.getArmor());
  std::cout << std::format("Dmg:{}-{}\n", mPlayer.getDamage().x, mPlayer.getDamage().y);
  std::cout << std::format("Skill points:{}\n\n", mPlayer.getSkillPoints());
  mPlayer.showPrimaryStats();
  mPlayer.showSecondaryStats();
  std::cout << mPlayer.showSkills();

  std::cout << "1. Distribute skillpoints\n";
  std::cout << "2. Exit\n";
}

void PlayerScreen::distributeSkillpoints()
{
  std::cout << std::format("You have {} skillpoints to distribute\n\n", mPlayer.getSkillPoints());
  std::cout << mPlayer.showSkills();
  std::cout << "What skill do you want to increase?\n";
  std::cout << "\nSkill name: ";

  mState = States::DISTRIBUTE_SKILLPOINTS;
}

void PlayerScreen::init()
{
}

void PlayerScreen::inputHandler()
{
  if (!mRenderScreen) {
  if (mState == States::DISTRIBUTE_SKILLPOINTS) {
    std::string menuItem{ 0 };
    std::cin >> menuItem;
    if (mPlayer.isSkillExist(menuItem) && mPlayer.getSkillPoints() >= mPlayer.getSkillValue(menuItem) + 1) {
      mPlayer.decreaseSkillPoints(mPlayer.getSkillValue(menuItem) + 1);
      mPlayer.increaseSkill(menuItem);
      mPlayer.updateStatsFromSkills();
    }
    mState = States::SHOW_STATS;
    system("cls");
  }
  else if (mState == States::SHOW_STATS) {
      size_t menuItem{ 0 };
      if (_kbhit()) {
        menuItem = _getch();
      }
      switch (menuItem) {
      case 49:
        mState = States::DISTRIBUTE_SKILLPOINTS;
        system("cls");
        break;
      case 50:
        system("cls");
        GameState::destroyScreen();
        break;
      default:
        std::cout << "Choose valid menu item\n\n";
        mState = States::SHOW_STATS;
        break;
      }
    }
   
    mRenderScreen = true;
  }
}

void PlayerScreen::update()
{
}

void PlayerScreen::render()
{
  if (mRenderScreen) {
    if (mState == States::SHOW_STATS) {
      showStats();
    }
    else if (mState == States::DISTRIBUTE_SKILLPOINTS) {
      distributeSkillpoints();
    }
    mRenderScreen = false;
  }
}