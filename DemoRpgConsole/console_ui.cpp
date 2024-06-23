#include "console_ui.h"
#include <iostream>
#include <format>
#include <memory>

// Show a divider of the user interface elements
void ConsoleUI::showDivider(char ch, size_t width)
{
  std::cout << std::string(width, ch) << "\n";
}

// Add the text to the appropriate container
void ConsoleUI::addToHud(UI_Type type, std::string str, size_t line)
{
  switch (type) {
  case UI_Type::PLAYER_INFO:
    mPlayerInfo.at(line) = std::move(str);
    break;
  case UI_Type::LOCATION_INFO:
    mLocationInfo.at(line) = std::move(str);
    break;
  case UI_Type::GAME_LOG:
    mGameLog.at(line) = std::move(str);
    break;
  }
}

void ConsoleUI::display(UI_Type type)
{
  std::array<std::string, 3> arrayToPrint;
  switch (type) {
  case UI_Type::PLAYER_INFO:
    arrayToPrint = mPlayerInfo;
    break;
  case UI_Type::LOCATION_INFO:
    arrayToPrint = mLocationInfo;
    break;
  case UI_Type::GAME_LOG:
    arrayToPrint = mGameLog;
    break;
  }

  for (const auto& str : arrayToPrint) {
    std::cout << str << '\n';
  }
  //std::cout << '\n';
}

void ConsoleUI::displayCommandString()
{
  std::cout << "Your action:\n";
  size_t counter{ 1 };
  for (const auto& str : mCommandsList) {
    std::cout << std::format("{}. {}\n", counter, str);
    counter++;
  }
}

void ConsoleUI::addCommand(std::string cmd)
{
  mCommandsList.push_back(cmd);
}

void ConsoleUI::clearCommandString()
{
  mCommandsList.clear();
}

void ConsoleUI::clear()
{
  mPlayerInfo.fill("");
  mLocationInfo.fill("");
  mGameLog.fill("");
}