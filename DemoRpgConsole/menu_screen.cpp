#include "menu_screen.h"
#include "game_state.h"
#include <iostream>
#include <format>
#include <conio.h>
#include "game_data.h"
#include "screen_manager.h"

void MenuScreen::showMainMenu()
{
  std::cout << "\n\n";
  std::cout << "\t\tConsole RPG ver 0.3.0\n\n";
  std::cout << "\t1. Play\n" << "\t2. Create a hero\n" << "\t3. Exit\n\n";
  std::cout << "\t\tDeveloped by Vargar\n\t\t\t2024";
}
 
void MenuScreen::init()
{
}

void MenuScreen::inputHandler()
{  
  if (!mRenderScreen) {
    size_t menuItem{ 0 };
    if (_kbhit()) {
      int menuItem = _getch();
      switch (menuItem) {
      case 49:
        system("cls");
        mRenderScreen = true;
        ScreenManager::createScreen(GameData::Screens::EXPLORE_SCREEN);
        break;
      case 50:
        system("cls");
        mRenderScreen = true;
        ScreenManager::createScreen(GameData::Screens::HERO_CREATION_SCREEN);
        break;
      case 51:
        exit(0);
        break;
      default:
        std::cout << "Choose valid menu item\n\n";
        mRenderScreen = true;
        break;
      }
    }
    mRenderScreen = true;
  }
}

void MenuScreen::update()
{
}

void MenuScreen::render()
{
  if (mRenderScreen) {
    showMainMenu();
    mRenderScreen = false;
  }
}