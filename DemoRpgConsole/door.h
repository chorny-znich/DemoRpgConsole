#pragma once

#include "game_object.h"

enum class DoorStatus {
  LOCKED,
  UNLOCKED
};

class Door : public GameObject
{
private:
  DoorStatus mStatus{ DoorStatus::LOCKED };

public:
  Door();

  void setStatus(DoorStatus status);
  DoorStatus getStatus() const;
};