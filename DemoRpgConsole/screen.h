#pragma once

/**
* @brief Abstract class for console game screens
*/  
class Screen {
public:
  virtual void init() = 0;
  virtual void inputHandler() = 0;
  virtual void update() = 0;
  virtual void render() = 0;
};