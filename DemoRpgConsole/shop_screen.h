#pragma once

#include "screen.h"
#include "shop.h"

class ShopScreen : public Screen
{
private: 
	enum class States {
		SHOW_SHOP_MENU,
		BUY_ITEM,
		SELL_ITEM
	};

private:
	Shop mShop;
  bool mRenderScreen;
	States mState;
	void showShopMenu();
	void showStaff();
	void showPlayerInventory();

public:
	ShopScreen();
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};