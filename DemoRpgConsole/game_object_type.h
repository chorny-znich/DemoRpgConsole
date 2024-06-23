#pragma once

enum class GameObjectType {
  MONEY,
  LADDER,
  POTION,
  WEAPON,
  ARMOR,
  DOOR,
  TRAP
};

enum class GameObjectSubType {
  NONE,
  HEALING_POTION,
  SWORD,
  CHEST,
  MELEE,
  RANGED
};