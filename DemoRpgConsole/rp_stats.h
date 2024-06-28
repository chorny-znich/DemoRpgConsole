// The roleplay system
// version 1
#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <SFML/System.hpp>
#include "game_data.h"

const size_t START_STATS_POINTS = 24;
const size_t MAX_HEALTH_MODIFIER = 3;
const float ATTACK_MODIFIER = 0.5;
const float DEFENCE_MODIFIER = 1.5;
const float ATTENTION_MODIFIER = 0.5;
const float REACTION_MODIFIER = 0.5;

class RPStats
{
protected:
	const std::map<size_t, size_t> LevelCap{
		{0, 0}, {1, 25}, {2, 100}, {3, 250}, {4, 500}, {5, 1000}
	};
	const std::map<size_t, std::unordered_map<std::string, size_t>> Adventurer{
		{1, {{"attack", 0}, {"defence", 0}, {"health", 5}, {"skill point", 1}}},
		{2, {{"attack", 0}, {"defence", 1}, {"health", 0}, {"skill point", 1}}},
		{3, {{"attack", 1}, {"defence", 0}, {"health", 5}, {"skill point", 1}}},
		{4, {{"attack", 0}, {"defence", 1}, {"health", 0}, {"skill point", 1}}},
		{5, {{"attack", 1}, {"defence", 0}, {"health", 5}, {"skill point", 2}}}
	};
	std::unordered_map<std::string, size_t> mPrimaryStats{
		{"Strength", 1},
		{"Stamina", 1},
		{"Dexterity", 1},
		{"Perception", 1},
		{"Intellect", 1},
		{"Charisma", 1}
	};
	std::unordered_map<std::string, size_t> mSecondaryStats{
		{"Attack", 0},
		{"Defence", 0},
		{"Attention", 0 },
		{"Reaction", 0}
	};
	std::unordered_map<std::string, size_t> mSkills {
		{"Search", 0},
		{"Athletic", 0},
		{"Dodge", 0 },
		{"Deft hands", 0}
	};

	std::string mName{ "Vargar" };
	size_t mExperience{ 0 };
	size_t mExperienceForKill{ 25 };
	std::size_t mMoney{ 0 };
	size_t mBaseDefence{ 0 };
	sf::Vector2u mDamage{ 0, 0 };
	size_t mArmor{ 0 };
	size_t mMaxHealth{ 10 };
	size_t mBaseMaxHealth{ 10 };
	size_t mHealth{ 10 };
	//GameData::RPClass mClass{ GameData::RPClass::Adventurer };
	size_t mLevel{ 0 };
	size_t mSkillPoints{ 0 };

public:
	void setName(const std::string& name);
	const std::string& getName() const;
	size_t getLevel() const;
	void setExperience(size_t exp);
	void increaseExperience(size_t exp);
	size_t getExperience() const;
	size_t& getExperience();
	void setExperienceForKill(size_t exp);
	size_t getExperienceForKill() const;
	void setMoney(size_t money);
	void increaseMoney(size_t money);
	void decreaseMoney(size_t money);
	size_t getMoney() const;
	size_t& getMoney();
	void setBaseDefence(size_t value);
	void updateDefence();
	void setDamage(sf::Vector2u dmg);
	sf::Vector2u getDamage() const;
	size_t getDamageValue() const;
	void setArmor(size_t armor);
	size_t getArmor() const;
	void setMaxHealth(size_t value);
	size_t getMaxHealth() const;
	void setBaseMaxHealth(size_t value);
	void updateMaxHealth();
	void setHealth(size_t value);
	void increaseHealth(size_t value);
	void decreaseHealth(size_t value);
	size_t getHealth() const;
	void updateAttention();

	// Primary stats
	void increasePrimaryStat(const std::string& str);
	void decreasePrimaryStat(const std::string& str);
	size_t getPrimaryStatValue(const std::string& str);
	void showPrimaryStats() const;
	// Secondary stats
	void setSecondaryStatValue(const std::string& str, size_t value);
	size_t getSecondaryStatValue(const std::string& str) const;
	void showSecondaryStats() const;
	// Skills
	void setSkillValue(const std::string& str, size_t value);
	void increaseSkill(const std::string& str);
	size_t getSkillValue(const std::string& str);
	bool isSkillExist(const std::string& name) const;
	std::string showSkills();
	void increaseSkillPoints(size_t value);
	void decreaseSkillPoints(size_t value);
	size_t getSkillPoints() const;
	void updateStatsFromSkills();
};