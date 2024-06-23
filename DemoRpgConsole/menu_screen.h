#pragma once

#include "screen.h"

class MenuScreen : public Screen
{
private:
	bool mRenderScreen{ true };
	void showMainMenu();

public:
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};