#pragma once
#include "screen.h"
#include "player.h"
#include "inventory.h"
#include "equipment.h"

class InventoryScreen : public Screen
{
private:
	enum class States {
		NONE,
		SHOW_LIST,
		SHOW_ITEM
	};
	States mState;

private:
	Player& mPlayer;
	Inventory& mInventory;
	Equipment& mEquipment;
	bool mRenderScreen;
	const size_t mInventorySize;
	size_t mCurrentItemIndex;
	void showInventory();
	void showEquipment();
	void showItem(size_t index);

public:
	InventoryScreen();
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};