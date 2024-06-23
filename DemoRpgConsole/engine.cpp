#include "engine.h"
#include "screen_manager.h"

#include <iostream> 
#include <format>
#include <string>
#include <Windows.h>

void Engine::init()
{
  HWND hWindowConsole = GetConsoleWindow();
  COORD bufferSize{ 1200, 800 };
  SetConsoleScreenBufferSize(hWindowConsole, bufferSize);
  MoveWindow(hWindowConsole, 600, 100, bufferSize.X, bufferSize.Y, TRUE);
  // get console handle
  mConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  // hide console cursor
  CONSOLE_CURSOR_INFO cursorInfo;
  cursorInfo.dwSize = 1;
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(mConsoleHandle, &cursorInfo);

  mData.init();
}

void Engine::input()
{ 
  if (!mGameState.isEmpty()) {
    mGameState.getCurrent()->inputHandler();
  }
}

void Engine::update()
{ 
  if (!mGameState.isEmpty()) {
    mGameState.getCurrent()->update();
  } 
}

/**
* @brief Render the console graphic from the current active screen
*/ 
void Engine::render()
{ 
  if (!mGameState.isEmpty()) {
    //system("cls");
    COORD cursorCoord;
    cursorCoord.X = 0;
    cursorCoord.Y = 0;
    SetConsoleCursorPosition(mConsoleHandle, cursorCoord);

    mGameState.getCurrent()->render();
  } 
}

void Engine::run() 
{
  init();
  ScreenManager::createScreen(GameData::Screens::MENU_SCREEN);

  while (mRunning && !mGameState.isEmpty()) {
    render();
    input();
    update();
  }
  system("cls");
  std::cout << std::format("The game is over\n");
}