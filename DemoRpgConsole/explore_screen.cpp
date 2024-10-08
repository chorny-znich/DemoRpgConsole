#include "explore_screen.h"
#include <iostream> 
#include <string>
#include <format> 
#include <conio.h>
#include "money.h"
#include "ladder.h"
#include "door.h"
#include "potion.h"
#include "weapon.h"
#include "armor.h"
#include "trap.h"
#include "arrow.h"
#include "battle.h"
#include "screen_manager.h" 
#include "game_state.h"
#include "ranged_battle.h"

#include <DisRealityGF.h>

ExploreScreen::ExploreScreen() :
  mCurrentMap{0},
  mStats{ mPlayer, mInventory, mEquipment },
  mBattleAction{mPlayer},
  mCurrentMapData{ mPlayer, mInventory, mEquipment }
{}

void ExploreScreen::init()
{
  mPlayer.create();
  mLevel.init();
  changeMap();   
}

void ExploreScreen::inputHandler()
{ 
  if (mState == GameplayState::PLAYER_INPUT) {
    if (_kbhit()) {
      mConsoleUI.clear();
      mConsoleUI.clearCommandString();
      system("cls");
      int cmd = _getch();
      switch (cmd) {
      case 113:
        GameState::destroyScreen();
        system("cls");
        break;
      case 97:
        mPlayer.moveWest();
        mPlayer.moving(true);
        break;
      case 100:
        mPlayer.moveEast();
        mPlayer.moving(true);
        break;
      case 119:
        mPlayer.moveNorth();
        mPlayer.moving(true);
        break;
      case 115:
        mPlayer.moveSouth();
        mPlayer.moving(true);
        break;
      case 103:
        useLadder();
        break;
      case 112:
        pickItem();
        break;
      case 98:
        showInventory();
        break;
      case 104:
        showStats(mPlayer);
        break;
      case 111:
        checkDoors(mPlayer.getPosition());
        break;
      case 116:
        if (checkNpcNearby(mPlayer.getPosition())) {
          showShop();
        }
        break;
      case 'f':
        saveGame();
        break;
      }
      mState = GameplayState::PLAYER_TURN;

      for (auto& actionItem : mHeroAction) {
        char actionCmd = actionItem.first + 48;
        if (cmd == actionCmd) {
          Action action = actionItem.second.second;
          if (action == Action::DISARM_TRAP) {
            Direction dir = actionItem.second.first;
            Location* loc = mHeroEnvironment[dir];
            if (disarmTrap(loc->getPosition())) {
              // Remove the trap
              loc->setObject(false);
              mObjectManager.destroyObject(loc->getPosition());
              loc->setSymbol(' ');
              // Show information in logs
              mConsoleUI.addToHud(UI_Type::LOCATION_INFO, showLocationInfo(), 0);
              mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You disarmed a trap"), 1);
            }
            else {
              mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You can't disarm a trap"), 1);
              checkHeroEnvironment(mPlayer.getPosition());
            }
          }
          else if (action == Action::SHOOT_NORTH) {
            if (mEquipment.hasConsumable("arrow") && mEquipment.getConsumable("arrow") > 0) {
              shoot(GameData::Direction::NORTH);
              mEquipment.decreaseConsumable("arrow", 1);
            }
            else {
              mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You don't have arrows"), 1);
            }
          }
          else if (action == Action::SHOOT_EAST) {
            if (mEquipment.hasConsumable("arrow") && mEquipment.getConsumable("arrow") > 0) {
              shoot(GameData::Direction::EAST);
              mEquipment.decreaseConsumable("arrow", 1);
            }
            else {
              mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You don't have arrows"), 1);
            }
          }
          else if (action == Action::SHOOT_SOUTH) {
            if (mEquipment.hasConsumable("arrow") && mEquipment.getConsumable("arrow") > 0) {
              shoot(GameData::Direction::SOUTH);
              mEquipment.decreaseConsumable("arrow", 1);
            }
            else {
              mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You don't have arrows"), 1);
            }
          }
          else if (action == Action::SHOOT_WEST) {
            if (mEquipment.hasConsumable("arrow") && mEquipment.getConsumable("arrow") > 0) {
              shoot(GameData::Direction::WEST);
              mEquipment.decreaseConsumable("arrow", 1);
            }
            else {
              mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You don't have arrows"), 1);
            }
          }
          mState = GameplayState::PLAYER_ACT;
        }
      }
    }
  }
}

void ExploreScreen::update()
{
  if (mState == GameplayState::PLAYER_TURN) {
    if (mPlayer.isMoving()) {
      if (battleDetection(mPlayer.getPosition(), mPlayer.getMovement())) {
        mPlayer.setDangerStatus(true);
        Enemy& enemy{ mEnemyManager.getEnemy({ mPlayer.getPosition().first + mPlayer.getMovement().first,
          mPlayer.getPosition().second + mPlayer.getMovement().second }) };
        mBattleAction.setCurrentEnemy(&enemy);
        showBattle();
        mState = GameplayState::PLAYER_ATTACK;
      }
      else if (fellTrap()) {
        GameData::Position currentPlayerLocation = { mPlayer.getPosition().first + mPlayer.getMovement().first,
          mPlayer.getPosition().second + mPlayer.getMovement().second };
        Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
        std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
        auto pTrapObject = std::static_pointer_cast<Trap>(pObject);
        // Check if the hero evade a trap
        std::string result{};
        size_t rollDice = dr::EngineUtility::getRandomInRange(GameData::DICE.x, GameData::DICE.y);
        mConsoleUI.addToHud(UI_Type::GAME_LOG,
          std::format("Stat: {} + Roll: {} vs Difficulty: {}", mPlayer.getSecondaryStatValue("Reaction"),
            rollDice, pTrapObject->getDifficulty()), 2);
        if (mPlayer.getSecondaryStatValue("Reaction") + rollDice < pTrapObject->getDifficulty()) {
          size_t trapDamage = dr::EngineUtility::getRandomInRange(pTrapObject->getDamage().x,
            pTrapObject->getDamage().y);
          mPlayer.decreaseHealth(trapDamage);
          if (mPlayer.getHealth() <= 0) {
            mConsoleUI.addToHud(UI_Type::GAME_LOG, "You killed by the trap", 1);
            GameState::destroyAllScreens();
          } 
          mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You got {} damage from the trap", trapDamage), 1);
        }
        else {
          mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You evade damage from the trap"), 1);
        }
                // Move the hero
        mCurrentMap.clearPlayer(mPlayer.getPosition());
        mPlayer.setDangerStatus(false);
        mPlayer.update();
        checkHeroEnvironment(mPlayer.getPosition());
        // Remove the trap
        location.setObject(false);
        mObjectManager.destroyObject(currentPlayerLocation);
        location.setSymbol(' ');
        // Show information in logs
        mConsoleUI.addToHud(UI_Type::LOCATION_INFO, showLocationInfo(), 0);

        mState = GameplayState::PLAYER_TURN_SHOW;
      }
      else if (mPlayer.isShooting()) {
        ScreenManager::createBattleScreen(GameData::BattleType::RANGED);
        mState = GameplayState::PLAYER_TURN_SHOW;
      }
      else if (!collisionDetection(mPlayer.getPosition(), mPlayer.getMovement())) {
        mCurrentMap.clearPlayer(mPlayer.getPosition()); 
        mPlayer.setDangerStatus(false);
        mPlayer.update();
        checkHeroEnvironment(mPlayer.getPosition());
        mConsoleUI.addToHud(UI_Type::GAME_LOG, "", 1);
        mConsoleUI.addToHud(UI_Type::LOCATION_INFO, showLocationInfo(), 0);
        mState = GameplayState::PLAYER_TURN_SHOW;
      } 
    }   
    else {
      mState = GameplayState::PLAYER_TURN_SHOW;
    }
  } 
  else if (mState == GameplayState::PLAYER_ATTACK) {
    Enemy& enemy{ mEnemyManager.getEnemy({ mPlayer.getPosition().first + mPlayer.getMovement().first,
      mPlayer.getPosition().second + mPlayer.getMovement().second }) };
    Battle battle(mPlayer, enemy); 
    mConsoleUI.addToHud(UI_Type::GAME_LOG, battle.playerAttack(BattleAction::getAction()), 1);
    if (!enemy.isActive()) {
      mCurrentMap.clearEnemy(enemy.getPosition());
    }
    mState = GameplayState::PLAYER_TURN_SHOW;
  }
  else if (mState == GameplayState::PLAYER_ACT) {
    mState = GameplayState::PLAYER_TURN_SHOW;
  }
  if (mState == GameplayState::ENEMY_TURN) {
    std::vector<Enemy>& enemies = mEnemyManager.getEnemies();
    mConsoleUI.addToHud(UI_Type::GAME_LOG, std::string{ std::format("") }, 2);
    for (auto& enemy : enemies) {
      if (enemy.isActive()) {
        // The enemy checks the environment
        std::map<GameData::Direction, std::vector<Location*>> locations;
        auto pos = enemy.getPosition();
        for (size_t i = 1; i <= enemy.getSight(); i++) {
          Location* pLoc = &mCurrentMap.getCurrentLocation({ pos.first, pos.second - i });
          locations[GameData::Direction::NORTH].push_back(pLoc);
          if (pLoc->isBarrier()) {
            break;
          }
        }
        for (size_t i = 1; i <= enemy.getSight(); i++) {
          Location* pLoc = &mCurrentMap.getCurrentLocation({ pos.first + i, pos.second });
          locations[GameData::Direction::EAST].push_back(pLoc);
          if (pLoc->isBarrier()) {
            break;
          }
        }
        for (size_t i = 1; i <= enemy.getSight(); i++) {
          Location* pLoc = &mCurrentMap.getCurrentLocation({ pos.first, pos.second + i });
          locations[GameData::Direction::SOUTH].push_back(pLoc);
          if (pLoc->isBarrier()) {
            break;
          }
        }
        for (size_t i = 1; i <= enemy.getSight(); i++) {
          Location* pLoc = &mCurrentMap.getCurrentLocation({ pos.first - i, pos.second });
          locations[GameData::Direction::WEST].push_back(pLoc);
          if (pLoc->isBarrier()) {
            break;
          }
        }
        enemy.checkEnvironment(locations);
        enemy.chooseAction();
        // enemy attack player
        if (enemy.isInBattle()) {
          Battle battle(mPlayer, enemy);
          mConsoleUI.addToHud(UI_Type::GAME_LOG, battle.enemyAttack(), 2);
          if (mPlayer.getHealth() <= 0) {
            GameState::destroyAllScreens();
            return;
          }
        }
        else {
          // enemy move
          enemy.move();
          if (!collisionDetection(enemy.getPosition(), enemy.getMovement()) &&
            (!battleDetection(enemy.getPosition(), enemy.getMovement()))) {
            mCurrentMap.clearEnemy(enemy.getPosition());
            enemy.update();
          }
        }
      } 
    }
    mState = GameplayState::ENEMY_TURN_SHOW;
  } 
  // Check for the objects visibility
  if (mState == GameplayState::START || mState == GameplayState::PLAYER_TURN_SHOW) {
    if (!mPlayer.getDangerStatus()) {
      checkEnvironment(mPlayer.getPosition());
    }
  }

  // prepare the current map and the interface to render
  if (mState == GameplayState::PLAYER_TURN_SHOW || mState == GameplayState::ENEMY_TURN_SHOW || 
    mState == GameplayState::START) {
    mCurrentMap.createRenderMap();
    mCurrentMap.setObjects(mObjectManager.getObjects());
    mCurrentMap.setEnemies(mEnemyManager.getEnemies());
    mCurrentMap.setNpcs(mNpcManager.getNpcs());
    mCurrentMap.setPlayer(mPlayer.getPosition());
    
    mConsoleUI.addToHud(UI_Type::PLAYER_INFO, std::string{ std::format("Name: {} lvl:{} exp:{} ${}", mPlayer.getName(), mPlayer.getLevel(),
      mPlayer.getExperience(), mPlayer.getMoney()) }, 0);
    mConsoleUI.addToHud(UI_Type::PLAYER_INFO, std::string{ std::format("HP:{}/{} ", mPlayer.getHealth(), mPlayer.getMaxHealth()) }, 1);
    mConsoleUI.addToHud(UI_Type::PLAYER_INFO, std::string{ std::format("Atk:{} Def:{}", 
      mPlayer.getSecondaryStatValue("Attack"), mPlayer.getSecondaryStatValue("Defence"))}, 2);
  }  
}

void ExploreScreen::render()
{ 
  if (mState == GameplayState::PLAYER_TURN_SHOW || mState == GameplayState::ENEMY_TURN_SHOW || 
    mState == GameplayState::START) {
    mConsoleUI.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
    mConsoleUI.display(UI_Type::PLAYER_INFO); 
    mCurrentMap.render();
    mConsoleUI.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
    mConsoleUI.display(UI_Type::LOCATION_INFO);
    mConsoleUI.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
    mConsoleUI.display(UI_Type::GAME_LOG);
    mConsoleUI.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
    mConsoleUI.displayCommandString();
    if (mState == GameplayState::ENEMY_TURN_SHOW || mState == GameplayState::START) {
      mState = GameplayState::PLAYER_INPUT;
    }
    else if (mState == GameplayState::PLAYER_TURN_SHOW) {
      mState = GameplayState::ENEMY_TURN;
    }
  }
}

bool ExploreScreen::collisionDetection(GameData::Position pos, GameData::Movement move)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  GameData::Position newPosition{ pos.first + move.first, pos.second + move.second };
  if (map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isBarrier() || 
    map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isEnemy()) {
    mPlayer.moving(false);
    return true;
  }
  
  return false;
}

bool ExploreScreen::battleDetection(GameData::Position pos, GameData::Movement move)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  GameData::Position newPosition{ pos.first + move.first, pos.second + move.second };
  if (map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isEnemy()) {
    mPlayer.moving(false);
    return true;
  }
  if (map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isPlayer()) {
    try {
      Enemy& enemy = mEnemyManager.getEnemy(pos);
      enemy.setBattleStatus(true);
    }
    catch (std::runtime_error re) {
      std::cout << std::format("{} in battleDetection()\n", re.what());
    }
    return true;
  }

  return false;
}

void ExploreScreen::pickItem()
{
  GameData::Position currentPlayerLocation = mPlayer.getPosition();
  Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
  if (location.isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
    if (pObject->getType() == GameObjectType::MONEY) {
      auto pMoneyObject = std::static_pointer_cast<Money>(pObject);
      mPlayer.increaseMoney(pMoneyObject->getAmount());
      mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("You pick up ${}", pMoneyObject->getAmount()), 1);
      location.setObject(false);
      mObjectManager.destroyObject(currentPlayerLocation);
      location.setSymbol(' ');
    } 
    else if (pObject->getType() == GameObjectType::POTION) {
        if (pObject->getSubType() == GameObjectSubType::HEALING_POTION) {
          auto pHealingPotionObject = std::static_pointer_cast<HealingPotion>(pObject);
          mInventory.add(pHealingPotionObject);
          mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("You pick up a healing potion"), 1);
          location.setObject(false);
          mObjectManager.destroyObject(currentPlayerLocation);
          location.setSymbol(' ');
        }
    }
    else if (pObject->getType() == GameObjectType::WEAPON) {
      auto pWeaponObject = std::static_pointer_cast<Weapon>(pObject);
      mInventory.add(pWeaponObject);
      mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("You pick up a {}", pWeaponObject->getName()), 1);
      location.setObject(false);
      mObjectManager.destroyObject(currentPlayerLocation);
      location.setSymbol(' ');
    }
    else if (pObject->getType() == GameObjectType::ARMOR) {
      auto pArmorObject = std::static_pointer_cast<Armor>(pObject);
      mInventory.add(pArmorObject);
      mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("You pick up a {}", pArmorObject->getName()), 1);
      location.setObject(false);
      mObjectManager.destroyObject(currentPlayerLocation);
      location.setSymbol(' ');
    }
    else if (pObject->getType() == GameObjectType::CONSUMABLE) {
      if (pObject->getSubType() == GameObjectSubType::ARROW) {
        auto pArrowObject = std::static_pointer_cast<Arrow>(pObject);
        if (mEquipment.hasConsumable("arrow")) {
          mEquipment.increaseConsumable("arrow", pArrowObject->getAmount());
        }
        else {
          mEquipment.addConsumable("arrow", pArrowObject->getAmount());
        }
        mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("You pick up {} arrows", pArrowObject->getAmount()), 1);
        location.setObject(false);
        mObjectManager.destroyObject(currentPlayerLocation);
        location.setSymbol(' ');
      }
    }
  }
  else {
    mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("Nothing to pick up here"), 1);
  } 
}

void ExploreScreen::useLadder()
{
  GameData::Position currentPlayerLocation = mPlayer.getPosition();
  Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
  if (location.isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
    if (pObject->getType() == GameObjectType::LADDER) {
      auto pLadderObject = std::static_pointer_cast<Ladder>(pObject);
      mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("You use the ladder"), 1);
      // Save the map's current state
      mLevelManager.setVisited();
      mLevelManager.saveCurrentState(mEnemyManager.getEnemies(), mObjectManager.getObjects(),
        mNpcManager.getNpcs());
      mLevel.setCurrentMapIndex(pLadderObject->getMapIndexTo());
      mLevelManager.setCurrentMapIndex(pLadderObject->getMapIndexTo());
      mLevel.setPlayerSpawnPosition(pLadderObject->getPlayerSpawnTo());
      changeMap();
    }
  }
  else {
    mConsoleUI.addToHud(UI_Type::LOCATION_INFO, std::format("There is no ladder here"), 1);
  }
}

void ExploreScreen::checkDoors(GameData::Position pos)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  const size_t RowSize = mCurrentMap.getMapSize().x;
  size_t index = pos.second * RowSize + pos.first;

  // check if the door is on the left from the player
  if (map.at(index - 1).isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first - 1, pos.second });
    if (pObject->getType() == GameObjectType::DOOR) {
      useDoor(pObject);
    }
  }
  // check if the player right of the door
  if (map.at(index + 1).isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first + 1, pos.second });
    if (pObject->getType() == GameObjectType::DOOR) {
      useDoor(pObject);
    }
  }
  // check if the player above the door
  if (map.at(index - RowSize).isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first, pos.second - 1 });
    if (pObject->getType() == GameObjectType::DOOR) {
      useDoor(pObject);
    }
  }
  // check if the player below the door
  if (map.at(index + RowSize).isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first, pos.second + 1 });
    if (pObject->getType() == GameObjectType::DOOR) {
      useDoor(pObject);
    }
  }
}

void ExploreScreen::useDoor(std::shared_ptr<GameObject> pObject)
{
  auto pDoor = std::static_pointer_cast<Door>(pObject);
  Location& location = mCurrentMap.getCurrentLocation(pDoor->getPosition());
  if (pDoor->getStatus() == DoorStatus::LOCKED) {
    pDoor->setStatus(DoorStatus::UNLOCKED);
    location.setBarrier(false);
  }
  else {
    pDoor->setStatus(DoorStatus::LOCKED);
    location.setBarrier(true);
  }
}
 
void ExploreScreen::showStats(Player& player)
{
  ScreenManager::createScreen(GameData::Screens::PLAYER_SCREEN);
}

void ExploreScreen::showInventory()
{
  ScreenManager::createScreen(GameData::Screens::INVENTORY_SCREEN);
}

bool ExploreScreen::checkNpcNearby(GameData::Position pos)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  const size_t RowSize = mCurrentMap.getMapSize().x;
  size_t index = pos.second * RowSize + pos.first;
  bool result{ false };
  // check if the npc left of the player
  if ((index % (RowSize) != 0) && (map.at(index - 1).isNpc())) {
    result = true;
    CurrentNpc::setNpc(std::make_unique<Npc>(mNpcManager.getNpc({ pos.first - 1, pos.second })));
  }
  // check if the npc right of the player
  else if ((index % (RowSize + 1) != 0) && (map.at(index + 1).isNpc())) {
    CurrentNpc::setNpc(std::make_unique<Npc>(mNpcManager.getNpc({ pos.first + 1, pos.second })));
    result = true;
  }
  // check if the npc above the player
  else if ((index >= RowSize) && (map.at(index - RowSize).isNpc())) {
    CurrentNpc::setNpc(std::make_unique<Npc>(mNpcManager.getNpc({ pos.first, pos.second - 1 })));
    result = true;
  }
  // check if the npc below the player
  else if ((index < mCurrentMap.getMapSize().y * RowSize - RowSize) && (map.at(index + RowSize).isNpc())) {
    result = true;
    CurrentNpc::setNpc(std::make_unique<Npc>(mNpcManager.getNpc({ pos.first, pos.second + 1 })));
  }

  return result;
}

void ExploreScreen::showShop()
{
  ScreenManager::createScreen(GameData::Screens::SHOP_SCREEN);
}

void ExploreScreen::showBattle()
{
  ScreenManager::createScreen(GameData::Screens::BATTLE_SCREEN);
}

std::string ExploreScreen::showLocationInfo()
{
  std::string result{"You see "};

  GameData::Position currentPlayerLocation = mPlayer.getPosition();
  Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
  if (location.isObject()) {
    try {
      std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
      if (pObject->getType() == GameObjectType::MONEY) {
        auto pMoneyObject = std::static_pointer_cast<Money>(pObject);
        result += std::format("${}", pMoneyObject->getAmount());
      }
      else if (pObject->getType() == GameObjectType::CONSUMABLE &&
        pObject->getSubType() == GameObjectSubType::ARROW) {
        auto pArrowObject = std::static_pointer_cast<Arrow>(pObject);
        result += std::format("{} arrows", pArrowObject->getAmount());
      }
      else {
        result += std::format("a {}", pObject->getName());
      }
    }
    catch (std::runtime_error re) {
      std::cout << std::format("{} in showLocationInfo()\n", re.what());
    }  
  }
  else {
    result += std::format(" nothing interesting here");
  }
  
  return result;
}

void ExploreScreen::changeMap()
{
  // Load a new current map 
  mCurrentMap = mLevel.getCurrentMap();
  mCurrentMap.createRenderMap();
  // Check if the player has visited the current map already
  if (mLevelManager.isVisited()) {
    mEnemyManager.createEnemies(mLevelManager.loadEnemies());
    mObjectManager.createObjects(mLevelManager.loadObjects());
    mNpcManager.createNpcs(mLevelManager.loadNpc());
  }
  else {
    mEnemyManager.createEnemies(mLevel.getCurrentEnemyListFilename());
    mCurrentMap.setEnemies(mEnemyManager.getEnemies());
    mNpcManager.createNpcs(mLevel.getCurrentNPCListFilename());
    mCurrentMap.setNpcs(mNpcManager.getNpcs());
    mObjectManager.createObjects(mLevel.getCurrentObjectListFilename());
    mCurrentMap.setObjects(mObjectManager.getObjects());
    mObjectManager.createRandomObjects(mCurrentMap);
    mCurrentMap.setObjects(mObjectManager.getObjects());
  }
  mPlayer.spawn(mLevel.getPlayerSpawnPosition());
  checkHeroEnvironment(mPlayer.getPosition());
  mState = GameplayState::START;
  // Share map's data with the CurrentMapData clas

  mCurrentMapData.changeMap(&(mEnemyManager.getEnemies()), &(mCurrentMap.getMap()), mCurrentMap.getMapSize());
}

void ExploreScreen::checkEnvironment(GameData::Position pos)
{
  // check if the object is on the left from the player
  if (mObjectManager.isObject({pos.first - 1, pos.second})) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first - 1, pos.second });
    if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
      pObject->setVisibleStatus(true);
    }
  }
  // check if the player right of the door
  if (mObjectManager.isObject({ pos.first + 1, pos.second })) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first + 1, pos.second });
    if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
      pObject->setVisibleStatus(true);
    }
  }
  // check if the player above the door
  if (mObjectManager.isObject({ pos.first, pos.second - 1 })) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first, pos.second - 1 });
    if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
      pObject->setVisibleStatus(true);
    }
  }
  // check if the player below the door
  if (mObjectManager.isObject({ pos.first, pos.second + 1 })) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first, pos.second + 1 });
    if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
      pObject->setVisibleStatus(true);
    }
  }
}
/**
 * @brief Check four locations that surrounds a hero
 * @param pos Hero's coords 
*/
void ExploreScreen::checkHeroEnvironment(GameData::Position pos)
{
  mHeroEnvironment[Direction::NORTH] = &mCurrentMap.getCurrentLocation({ pos.first, pos.second - 1 });
  mHeroEnvironment[Direction::EAST] = &mCurrentMap.getCurrentLocation({ pos.first + 1, pos.second });
  mHeroEnvironment[Direction::SOUTH] = &mCurrentMap.getCurrentLocation({ pos.first, pos.second + 1 });
  mHeroEnvironment[Direction::WEST] = &mCurrentMap.getCurrentLocation({ pos.first - 1, pos.second });

  for (const auto& item : mHeroEnvironment) {
    GameData::Position locPosition = item.second->getPosition();
    if (item.second->isObject()) {
      auto pObject = mObjectManager.getObject(locPosition);
      if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
        pObject->setVisibleStatus(true);
      }
      if (pObject->isVisible() && pObject->getType() == GameObjectType::TRAP) {
        size_t currentCommandNumber = mConsoleUI.getCurrentCommandNumber() + 1;
        mHeroAction[currentCommandNumber] = {item.first, Action::DISARM_TRAP};
        mConsoleUI.addCommand(std::format("{}. {}", currentCommandNumber, mActionList[Action::DISARM_TRAP]));
      }
      
    }
  }
  mConsoleUI.addCommand(std::format("{}. {}", mConsoleUI.getCurrentCommandNumber() + 1, 
    mActionList[Action::SHOOT_NORTH]));
  mHeroAction[mConsoleUI.getCurrentCommandNumber()] = { Direction::NORTH, Action::SHOOT_NORTH };
  mConsoleUI.addCommand(std::format("{}. {}", mConsoleUI.getCurrentCommandNumber() + 1, 
    mActionList[Action::SHOOT_EAST]));
  mHeroAction[mConsoleUI.getCurrentCommandNumber()] = { Direction::EAST, Action::SHOOT_EAST };
  mConsoleUI.addCommand(std::format("{}. {}", mConsoleUI.getCurrentCommandNumber() + 1, 
    mActionList[Action::SHOOT_SOUTH]));
  mHeroAction[mConsoleUI.getCurrentCommandNumber()] = { Direction::SOUTH, Action::SHOOT_SOUTH };
  mConsoleUI.addCommand(std::format("{}. {}", mConsoleUI.getCurrentCommandNumber() + 1, 
    mActionList[Action::SHOOT_WEST]));
  mHeroAction[mConsoleUI.getCurrentCommandNumber()] = { Direction::WEST, Action::SHOOT_WEST };
}

bool ExploreScreen::checkVisibility(size_t value)
{
  size_t randomValue = dr::EngineUtility::getRandomInRange(GameData::DICE.x, GameData::DICE.y);
  mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("Search Skill:{} Dice:{} Value to check:{} ???\n",
    mPlayer.getSecondaryStatValue("Attention"),
    randomValue, value), 0);
  return (mPlayer.getSecondaryStatValue("Attention") + randomValue >= value) ? true : false;
}

void ExploreScreen::saveGame()
{
  mPlayer.save();
  mEquipment.save();
  mInventory.save();
}

void ExploreScreen::shoot(GameData::Direction direction)
{
  //mPlayer.shooting(true);
  RangedBattle rangedBattle(direction);
  mConsoleUI.addToHud(UI_Type::GAME_LOG, rangedBattle.shoot(), 1);

  mState = GameplayState::PLAYER_TURN_SHOW;
}
/**
 * @brief Check if the player fell into a trap
 * @return Result of checking
*/
bool ExploreScreen::fellTrap()
{
  bool result = false;
  GameData::Position currentPlayerLocation = { mPlayer.getPosition().first + mPlayer.getMovement().first,
          mPlayer.getPosition().second + mPlayer.getMovement().second };
  Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
  if (location.isObject()) {
    try {
      std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
      if (pObject->getType() == GameObjectType::TRAP) {
        auto pTrapObject = std::static_pointer_cast<Trap>(pObject);
        result = true;
      }
    }
    catch (std::runtime_error re) {
      std::cout << std::format("{} in showLocationInfo()\n", re.what());
    }
  }
  return result;
}

/**
 * @brief Hero try to disarm a trap
 * @return checking result 
*/
bool ExploreScreen::disarmTrap(GameData::Position pos)
{
  bool result = false;
  std::shared_ptr<GameObject> pObject = mObjectManager.getObject(pos);
  auto pTrapObject = std::static_pointer_cast<Trap>(pObject);
  size_t difficulty = pTrapObject->getDifficulty();
  size_t skillValue = mPlayer.getSkillValue("Deft hands");
  std::string resultString{};
  size_t rollDice = dr::EngineUtility::getRandomInRange(GameData::DICE.x, GameData::DICE.y);
  mConsoleUI.addToHud(UI_Type::GAME_LOG,
    std::format("Skill: {} + Roll: {} vs Difficulty: {}", skillValue, rollDice, difficulty), 2);
  if (skillValue + rollDice >= difficulty) {
    result = true;
    mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You disarmed a trap"), 1);
  }
  else {
    mConsoleUI.addToHud(UI_Type::GAME_LOG, std::format("You didn't disarm a trap"), 1);
  }
  return result;
}