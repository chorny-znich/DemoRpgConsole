#include "rp_stats.h"
#include <DisRealityGF.h>

void RPStats::setName(const std::string& name)
{
	mName = name;
}
const std::string& RPStats::getName() const
{
	return mName;
}

size_t RPStats::getLevel() const
{
	return mLevel;
}

void RPStats::setExperience(size_t exp)
{
	mExperience = exp;
}

void RPStats::increaseExperience(size_t exp)
{
	mExperience += exp;
}

size_t RPStats::getExperience() const
{
	return mExperience;
}

size_t& RPStats::getExperience()
{
	return mExperience;
}

void RPStats::setExperienceForKill(size_t exp)
{
	mExperienceForKill = exp;
}

size_t RPStats::getExperienceForKill() const
{
	return mExperienceForKill;
}

void RPStats::setMoney(size_t money)
{
	mMoney = money;
}

void RPStats::increaseMoney(size_t money)
{
	mMoney += money;
}

void RPStats::decreaseMoney(size_t money)
{
	mMoney = (money > mMoney) ? 0 : mMoney - money;
}

size_t RPStats::getMoney() const
{
	return mMoney;
}

size_t& RPStats::getMoney()
{
	return mMoney;
}

void RPStats::setBaseDefence(size_t value)
{
	mBaseDefence = value;
}

void RPStats::updateDefence()
{
	size_t result = mBaseDefence;
	for (size_t i = 1; i < mLevel; i++) {
		result += Adventurer.at(i).at("defence");
	}
	result += mSkills.at("Dodge");
	setSecondaryStatValue("Defence", result);
}

void RPStats::setDamage(sf::Vector2u dmg)
{
	mDamage = dmg;
}

sf::Vector2u RPStats::getDamage() const
{
	return mDamage;
}

size_t RPStats::getDamageValue() const
{
	return dr::EngineUtility::getRandomInRange(mDamage.x, mDamage.y);
}

void RPStats::setArmor(size_t armor)
{
	mArmor = armor;
}

size_t RPStats::getArmor() const
{
	return mArmor;
}

void RPStats::setMaxHealth(size_t value)
{
	mMaxHealth = value;
}

size_t RPStats::getMaxHealth() const
{
	return mMaxHealth;
}

void RPStats::setBaseMaxHealth(size_t value)
{
	mBaseMaxHealth = value;
}

void RPStats::updateMaxHealth()
{
	size_t result = mBaseMaxHealth;
	for (size_t i = 1; i <= mLevel; i++) {
		result += Adventurer.at(i).at("health");
	}
	result += mSkills.at("Athletic") * 5;
	setMaxHealth(result);
}

void RPStats::setHealth(size_t value)
{
	mHealth = value;
}

void RPStats::increaseHealth(size_t value)
{
	if (mMaxHealth >= mHealth + value) {
		mHealth += value;
	}
	else {
		mHealth = mMaxHealth;
	}
}

void RPStats::decreaseHealth(size_t value)
{
	mHealth = (mHealth > value) ? mHealth - value : 0;	
}

size_t RPStats::getHealth() const
{
	return mHealth;
}

void RPStats::updateAttention()
{
	setSecondaryStatValue("Attention", std::floor(getPrimaryStatValue("Perception") * ATTENTION_MODIFIER) + getSkillValue("Search"));
}

void RPStats::setSecondaryStatValue(const std::string& str, size_t value)
{
	mSecondaryStats[str] = value;
}

size_t RPStats::getSecondaryStatValue(const std::string& str) const
{
	return mSecondaryStats.at(str);
}

void RPStats::showSecondaryStats() const
{
	std::cout << "Secondary stats:\n";
	std::cout << std::format("  Money - {}\n", getMoney());
	std::cout << std::format("  Health - {}\n", getMaxHealth());
	std::cout << std::format("  Attack - {}\n", getSecondaryStatValue("Attack"));
	std::cout << std::format("  Defence - {}\n", getSecondaryStatValue("Defence"));
	std::cout << std::format("  Attention - {}\n", getSecondaryStatValue("Attention"));
	std::cout << std::format("  Reaction - {}\n", getSecondaryStatValue("Reaction"));
	std::cout << "\n";
}

void RPStats::showPrimaryStats() const
{
	std::cout << "Primary stats:\n";
	for (const auto& stat : mPrimaryStats) {
		std::cout << std::format("  {} - {}\n", stat.first, stat.second); 
	}
	std::cout << "\n";
}

void RPStats::increasePrimaryStat(const std::string& str)
{
	mPrimaryStats[str] += 1;
}

void RPStats::decreasePrimaryStat(const std::string& str)
{
	mPrimaryStats[str] -= 1;
}

size_t RPStats::getPrimaryStatValue(const std::string& str)
{
	return mPrimaryStats[str];
}

void RPStats::setSkillValue(const std::string& str, size_t value)
{
	mSkills[str] = value;
}

void RPStats::increaseSkill(const std::string& str)
{
	mSkills[str] += 1;
}

size_t RPStats::getSkillValue(const std::string& str)
{
	return mSkills[str];
}

bool RPStats::isSkillExist(const std::string& name) const
{
	return (mSkills.find(name) != mSkills.end()) ? true : false;
}

std::string RPStats::showSkills()
{
	std::string result{};
	result.append("Skills:\n");
	for (const auto& [skill, value] : mSkills) {
		result.append(std::format("  {} -- {}\n", skill, value));
	}
	result.append("\n");

	return result;
}

void RPStats::increaseSkillPoints(size_t value)
{
	mSkillPoints += value;
}

void RPStats::decreaseSkillPoints(size_t value)
{
	mSkillPoints -= value;
}

size_t RPStats::getSkillPoints() const
{
	return mSkillPoints;
}

void RPStats::updateStatsFromSkills()
{
	updateMaxHealth();
	updateDefence();
}