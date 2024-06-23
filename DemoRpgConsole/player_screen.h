#pragma once

#include "screen.h"
#include "player.h"

class PlayerScreen : public Screen
{
private:
	enum class States {
		SHOW_STATS,
		DISTRIBUTE_SKILLPOINTS
	};
	States mState;
	Player& mPlayer;
	bool mRenderScreen;
	void showStats();
	void distributeSkillpoints();

public:
	PlayerScreen();
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};