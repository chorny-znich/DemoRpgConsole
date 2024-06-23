#include "hero_creation_screen.h"
#include "game_state.h"
#include "game_data.h"
#include <iostream>
#include <format>
#include <conio.h>
#include <cmath>
#include <fstream>

void HeroCreationScreen::setPlayerName()
{
  std::string name;
  std::cout << "What's your name? ";
  std::cin >> name;
  mPlayer.setName(std::move(name));
}

void HeroCreationScreen::showScreen()
{
  std::cout << "Create your hero. Choose your name and distribute points for hero's stats.\n\n";
  std::cout << std::format("Name: {}\n", mPlayer.getName());
  std::cout << std::format("Number of points to distribute is {}\n\n", mStatsPoints);
  std::cout << "Primary stats:\n";
  showPrimaryStats();
  mPlayer.showSecondaryStats();
  mPlayer.showSkills();
  std::cout << "\nNavigate between stats with 'w' and 's' keys.\nPress 'a' to decrease stat's value and 'd' to increase it.\n";
  std::cout << "Press 'Space' when you distribute all stats points.\n";
}

void HeroCreationScreen::calcSecondaryStats()
{
  mPlayer.setMoney(mPlayer.getPrimaryStatValue("Intellect") * mPlayer.getPrimaryStatValue("Charisma"));
  mPlayer.setMaxHealth(mPlayer.getPrimaryStatValue("Stamina") * MAX_HEALTH_MODIFIER);
  mPlayer.setSecondaryStatValue("Attack", std::floor(mPlayer.getPrimaryStatValue("Strength") * ATTACK_MODIFIER));
  mPlayer.setSecondaryStatValue("Defence", std::floor(mPlayer.getPrimaryStatValue("Dexterity") * DEFENCE_MODIFIER));
  mPlayer.updateAttention();
}

void HeroCreationScreen::createHero()
{
  std::ofstream ofs(GameData::path::PlayerInfo);
  if (ofs) {
    ofs << "[Player]\n";
    ofs << "Name=" << mPlayer.getName() << "\n";
    ofs << "Experience=0\n";
    ofs << "Health=" << mPlayer.getMaxHealth() << "\n";
    ofs << "Damage_min=1\n";
    ofs << "Damage_max=1\n";
    ofs << "Position_x=1\n";
    ofs << "Position_y=1\n";
    ofs << "Symbol=@\n";
    ofs << "Money=" << mPlayer.getMoney() << "\n\n";
    ofs << "[Primary stats]\n";
    for (const auto& stat : mStatsList) {
      ofs << stat << "=" << mPlayer.getPrimaryStatValue(stat) << "\n";
    }
    ofs << "\n[Secondary stats]\n";
    for (const auto& stat : mSecondaryStatsList) {
      ofs << stat << "=" << mPlayer.getSecondaryStatValue(stat) << "\n";
    }
    ofs << "\n[Skills]\n";
    for (const auto& skill : mSkillsList) {
      ofs << skill << "=" << mPlayer.getSkillValue(skill) << "\n";
    }
  }
  else {
    std::cout << "\nCan't create a file with player's information\n";
  }
}

void HeroCreationScreen::showPrimaryStats()
{
  for (size_t i = 0; i < mStatsList.size(); i++) {
    std::string result{};
    if (mMenuIndex == i) {
      result = "* " + mStatsList[i] + " - " + std::to_string(mPlayer.getPrimaryStatValue(mStatsList[i]));
    }
    else {
      result = "  " + mStatsList[i] + " - " + std::to_string(mPlayer.getPrimaryStatValue(mStatsList[i]));
    }
    std::cout << result << "\n";
  }
  std::cout << "\n\n";
}

void HeroCreationScreen::init()
{
  setPlayerName();
  calcSecondaryStats();
}

void HeroCreationScreen::inputHandler()
{
  if (_kbhit()) {
    char action = _getch();
    switch (action) {
    case 'w':
      if (mMenuIndex > 0) {
        mMenuIndex--;
      }
      break;
    case 's':
      if (mMenuIndex < mStatsList.size() - 1) {
        mMenuIndex++;
      }
      break;
    case 'd':
      if (mStatsPoints > 0 && mPlayer.getPrimaryStatValue(mStatsList[mMenuIndex]) < 10) {
        mPlayer.increasePrimaryStat(mStatsList[mMenuIndex]);
        mStatsPoints--;
        calcSecondaryStats();
      }
      break;
    case 'a':
      if (mStatsPoints < START_STATS_POINTS && mPlayer.getPrimaryStatValue(mStatsList[mMenuIndex]) > 1) {
        mPlayer.decreasePrimaryStat(mStatsList[mMenuIndex]);
        mStatsPoints++;
        calcSecondaryStats();
      }
      break;
    case 32:
      if (mStatsPoints == 0) {
        createHero();
        std::cout << "\nYou create a hero. Now you can start a new game.\n";
        system("cls");
        GameState::destroyScreen();
      }
      break;
    }
    mRenderScreen = true;
  }
}

void HeroCreationScreen::update()
{
}

void HeroCreationScreen::render()
{
  if (mRenderScreen) {
    system("cls");
    showScreen();
    mRenderScreen = false;
  }
}