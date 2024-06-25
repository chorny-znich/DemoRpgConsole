#pragma once
#include <utility>

using Position = std::pair<size_t, size_t>;

class Location
{
private:
  Position mPosition;
  char mSymbol;
  bool mBarrier{ false };
  bool mPlayer{ false };
  bool mEnemy{ false };
  bool mObject{ false };
  bool mNpc{ false };

public:
  void setPosition(Position pos);
  Position getPosition() const;
  void setSymbol(char ch);
  char getSymbol() const; 
  void setBarrier(bool value);
  bool isBarrier() const;
  void setPlayer(bool value);
  bool isPlayer() const;
  void setEnemy(bool value);
  bool isEnemy() const;
  void setObject(bool value);
  bool isObject() const;
  void setNPC(bool value);
  bool isNpc() const;
};