#pragma once

#include "game_object.h"

enum class DoorStatus {
  OPEN,
  CLOSED,
  LOCKED,
  HIDDEN
};

class Door : public GameObject
{
private:
  DoorStatus mStatus{ DoorStatus::CLOSED };

public:
  Door();

  void setStatus(DoorStatus status);
  DoorStatus getStatus() const;
};