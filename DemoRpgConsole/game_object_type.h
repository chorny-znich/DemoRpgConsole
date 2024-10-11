#pragma once

enum class GameObjectType {
  MONEY,
  LADDER,
  POTION,
  WEAPON,
  ARMOR,
  DOOR,
  TRAP,
  CONSUMABLE
};

enum class GameObjectSubType {
  NONE,
  HEALING_POTION,
  SWORD,
  CHEST,
  MELEE,
  RANGED,
  ARROW,
  INGRIDIENT
};