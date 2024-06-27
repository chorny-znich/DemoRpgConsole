#pragma once

#include <array>
#include <vector>
#include <string>

enum class UI_Type {
  PLAYER_INFO,
  LOCATION_INFO,
  GAME_LOG
};

class ConsoleUI
{
private:
  std::array<std::string, 3> mPlayerInfo;
  std::array<std::string, 3> mLocationInfo;
  std::array<std::string, 3> mGameLog;
  std::string mCommandString;
  std::vector<std::string> mCommandsList;

public:  
  void showDivider(char ch, size_t width);
  void addToHud(UI_Type type, std::string str, size_t line);
  void display(UI_Type type);
  void displayCommandString();
  void addCommand(std::string cmd);
  void clearCommandString();
  size_t getCurrentCommandNumber() const;
  void clear();
};