#pragma once

#include "game_state.h"
#include "data.h"
#include <Windows.h>

class Engine
{ 
private:
  HANDLE mConsoleHandle;
  GameState mGameState;
  Data mData;
  
  bool mRunning{ true };

  void init();
  void input();
  void update();
  void render();
  
public:
  void run();
};