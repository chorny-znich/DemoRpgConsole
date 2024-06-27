#pragma once
#include "screen.h"
#include "player.h"
#include <array>
#include <string>

class HeroCreationScreen : public Screen
{
private:
  size_t STATS_NUMBER{ 6 };
  std::array<std::string, 6> mStatsList{
    "Strength",
    "Stamina",
    "Dexterity",
    "Perception",
    "Intellect",
    "Charisma"
  };
  std::array<std::string, 4> mSecondaryStatsList{
    "Attack",
    "Defence",
    "Attention",
    "Reaction"
  };
  size_t SKILLS_NUMBER{ 3 };
  std::array<std::string, 3> mSkillsList{
    "Search",
    "Athletic",
    "Dodge"
  };

private:
  Player mPlayer;
  size_t mStatsPoints{ START_STATS_POINTS };
  size_t mMenuIndex{ 0 };
  bool mRenderScreen{ true };

  void setPlayerName();
  void showScreen();
  void showPrimaryStats();
  void calcSecondaryStats();
  void createHero();

public:
  void init();
  void inputHandler();
  void update();
  void render();
};