#include "shop_screen.h"
#include "game_state.h"
#include "current_npc.h"
#include <iostream>
#include <format>
#include <conio.h>
#include <string>

ShopScreen::ShopScreen() :
  mShop{ CurrentNpc::getNpc() },
  mRenderScreen{ true },
  mState{States::SHOW_SHOP_MENU}
{
}

void ShopScreen::showShopMenu()
{
  std::cout << "Trader ask you: \"Do you want to buy or sell the staff?\"\n\n";
  std::cout << "1. Buy\n2. Sell\n3. Exit\n\n";

  std::cout << "Your action: ";
}

void ShopScreen::showStaff()
{
  std::cout << mShop.show();
  std::cout << std::format("\n{}. Exit\n\n", mShop.getSize() + 1);
  std::cout << "Which item do you want to buy? ";
}

void ShopScreen::showPlayerInventory()
{
  std::cout << mShop.getInventory().show();
  std::cout << std::format("\n{}. Exit\n\n", mShop.getInventory().getSize() + 1);
  std::cout << "Your action: ";
}

void ShopScreen::init()
{
}

void ShopScreen::inputHandler()
{ 
  if (!mRenderScreen) {
    if (_kbhit()) {
      char menuItem = _getch();
      size_t itemIndex = menuItem - '0';
      switch (mState) {
      case States::SHOW_SHOP_MENU:
        switch (menuItem) {
        case 49:
          mState = States::BUY_ITEM;
          system("cls");
          break;
        case 50:
          mState = States::SELL_ITEM;
          system("cls");
          break;
        case 51:
          system("cls");
          GameState::destroyScreen();
          break;
        default:
          break;
        }
        break;
      case States::BUY_ITEM:
        if (itemIndex > 0 && itemIndex <= mShop.getSize()) {
          mShop.buy(itemIndex - 1);
        }
        else if (itemIndex == mShop.getSize() + 1) {
          mState = States::SHOW_SHOP_MENU;
          system("cls");
        }
        break;
      case States::SELL_ITEM:
        if (itemIndex > 0 && itemIndex <= mShop.getInventory().getSize()) {
          mShop.sell(itemIndex - 1);
          mState = States::SHOW_SHOP_MENU;
          system("cls");
        }
        else if (itemIndex == mShop.getInventory().getSize() + 1) {
          mState = States::SHOW_SHOP_MENU;
          system("cls");
        }
        break;
      }
      mRenderScreen = true;
    }
  }
}

void ShopScreen::update()
{
}

void ShopScreen::render()
{
  if (mRenderScreen) {
    if (mState == States::SHOW_SHOP_MENU) {
      showShopMenu();
    }
    else if (mState == States::BUY_ITEM) {
      showStaff();
    }
    else if (mState == States::SELL_ITEM) {
      showPlayerInventory();
    }
    mRenderScreen = false;
  }
}
