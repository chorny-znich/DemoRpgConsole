#include "player.h"
#include "DisRealityGF.h"
#include <fstream>

Player::Player()
{
}

void Player::create()
{
  ini::Document doc = ini::load(GameData::path::PlayerInfo);
  ini::Section section = doc.getSection("Player");
  setSymbol(section.at("Symbol")[0]);
  setName(section.at("Name"));
  setExperience(std::stoi(section.at("Experience")));
  setBaseMaxHealth(std::stoi(section.at("Health")));
  updateMaxHealth();
  setHealth(std::stoul(section.at("Health")));
  
  spawn({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
  setDamage({ std::stoul(section.at("Damage_min")), std::stoul(section.at("Damage_max")) });
  setMoney({std::stoul(section.at("Money"))});
  // set Stats
  section = doc.getSection("Primary stats");
  for (auto& stat : mPrimaryStats) {
    stat.second = std::stoul(section.at(stat.first));
  }
  // Set secondary stats
  section = doc.getSection("Secondary stats");
  for (auto& stat : mSecondaryStats) {
    stat.second = std::stoul(section.at(stat.first));
  }
  setBaseDefence(std::stoul(section.at("Defence")));
  updateDefence();
  // set Skills
  section = doc.getSection("Skills");
  for (auto& skill : mSkills) {
    skill.second = std::stoul(section.at(skill.first));
  }
}

void Player::save()
{
  std::ofstream ofs(GameData::path::Save);
  if (ofs) {
    ofs << "[Player]\n";
    ofs << "Name=" << getName() << "\n";
    ofs << "Experience=" << getExperience() << "\n";
    ofs << "Max_Health=" << getMaxHealth() << "\n";
    ofs << "Health=" << getHealth() << "\n";
    ofs << "Damage_min=" << getDamage().x << "\n";
    ofs << "Damage_max=" << getDamage().y << "\n";
    //ofs << "Position_x=1\n";
    //ofs << "Position_y=1\n";
    ofs << "Symbol=@\n";
    ofs << "Money=" << getMoney() << "\n\n";
    ofs << "[Primary stats]\n";
    for (const auto& stat : mPrimaryStats) {
      ofs << stat.first << "=" << stat.second << "\n";
    }
    ofs << "\n[Secondary stats]\n";
    for (const auto& stat : mSecondaryStats) {
      ofs << stat.first << "=" << stat.second << "\n";
    }
    ofs << "\n[Skills]\n";
    for (const auto& skill : mSkills) {
      ofs << skill.first << "=" << skill.second << "\n";
    }
  }
  else {
    std::cout << "\nCan't create a save file\n";
  }
}

void Player::update()
{
    mPosition.first += mMovement.first;
    mPosition.second += mMovement.second;
    moving(false);
}

void Player::moveWest() {
  mMovement = { -CHAR_STEP, 0 };
}

void Player::moveEast() {
  mMovement = { CHAR_STEP, 0 };
}

void Player::moveNorth() {
  mMovement = { 0 , -CHAR_STEP };
}

void Player::moveSouth() {
  mMovement = { 0 , CHAR_STEP };
}

void Player::moving(bool move) {
  mMoving = move;
}

bool Player::isMoving() const
{
  return mMoving;
}

void Player::shooting(bool shoot)
{
  mShooting = shoot;
}

bool Player::isShooting() const
{
  return mShooting;
}

void Player::setDangerStatus(bool status)
{
  mDangerStatus = status;
}

bool Player::getDangerStatus() const
{
  return mDangerStatus;
}

bool Player::levelupCheck()
{
  if (mExperience >= LevelCap.at(mLevel + 1)) {
    levelup();
    return true;
  }

  return false;
}

void Player::levelup()
{
  mLevel++;
  setSecondaryStatValue("Attack", getSecondaryStatValue("Attack") + Adventurer.at(mLevel).at("attack"));
  setSecondaryStatValue("Defence", getSecondaryStatValue("Defence") + Adventurer.at(mLevel).at("defence"));
  updateMaxHealth();
  increaseSkillPoints(Adventurer.at(mLevel).at("skill point"));
}