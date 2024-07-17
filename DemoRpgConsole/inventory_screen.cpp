#include "inventory_screen.h"
#include "stats.h"
#include "game_state.h"
#include "game_object_type.h"
#include "potion.h"
#include "weapon.h"
#include "armor.h"
#include <iostream>
#include <format>
#include <string>
#include <conio.h>

InventoryScreen::InventoryScreen() :
  mState{States::SHOW_LIST},
  mPlayer{ Stats::getPlayer() },
  mInventory{ Stats::getInventory() },
  mEquipment{ Stats::getEquipment() },
  mRenderScreen{ true },
  mInventorySize{ mInventory.getSize() },
  mCurrentItemIndex{0}
{
}

void InventoryScreen::showInventory()
{
  std::cout << mInventory.show();
  std::cout << std::format("\n0. Exit\n\n");
}

void InventoryScreen::showEquipment()
{
  std::cout << mEquipment.show();
  mRenderScreen = true;
}

void InventoryScreen::showItem(size_t index)
{
  auto pCurrentItem = mInventory.getItem(index);
  std::cout << std::format("\t{}\n\n", pCurrentItem->getName());

  std::cout << "1. Equip/Use\n2. Exit\n";
}

void InventoryScreen::init()
{
}

void InventoryScreen::inputHandler()
{
  if (!mRenderScreen) {
    if (_kbhit()) {
      if (mState == States::SHOW_LIST) {
        const int EXIT_NUMBER = mInventorySize + 1;
        const char EXIT_NUMBER_CODE = 48;
        int menuItemCode{ _getch() };
        int menuItem = menuItemCode - '0';

        if (menuItemCode == EXIT_NUMBER_CODE) {
          system("cls");
          GameState::destroyScreen();
        }
        else if (menuItemCode > '9' || menuItemCode < '1') {
          std::cout << "Choose valid menu item\n\n";
        }
        else {
          mCurrentItemIndex = menuItem - 1;
          mState = States::SHOW_ITEM;
          system("cls");
        }
      }
      else if (mState == States::SHOW_ITEM) {
        int menuItemCode{ _getch() };
        int menuItem = menuItemCode - '0';

        if (menuItem == 1) {
          auto pCurrentItem = mInventory.getItem(mCurrentItemIndex);

          if (pCurrentItem->getType() == GameObjectType::POTION) {
            if (pCurrentItem->getSubType() == GameObjectSubType::HEALING_POTION) {
              auto healingPotion = std::static_pointer_cast<HealingPotion>(pCurrentItem);
              mPlayer.increaseHealth(healingPotion->drink());
            }
            mInventory.destroyItem(mCurrentItemIndex);
          }
          else if (pCurrentItem->getType() == GameObjectType::WEAPON) {
            mEquipment.equip(pCurrentItem);
            auto pWeapon = std::static_pointer_cast<Weapon>(pCurrentItem);
            if (pWeapon->getWeaponType() == WeaponType::MELEE) {
              mPlayer.setDamage({ pWeapon->getDamage().x, pWeapon->getDamage().y });
            }
            else if (pWeapon->getWeaponType() == WeaponType::RANGED) {
              mPlayer.setRangedDamage({ pWeapon->getDamage().x, pWeapon->getDamage().y });
            }
          }
          else if (pCurrentItem->getType() == GameObjectType::ARMOR) {
            mEquipment.equip(pCurrentItem);
            auto pArmor = std::static_pointer_cast<Armor>(pCurrentItem);
            mPlayer.setArmor({ pArmor->getArmor() });
          }
          mState = States::SHOW_LIST;
          system("cls");
        }
        else if (menuItem == 2) {
          mState = States::SHOW_LIST;
          system("cls");
        }
      }
      mRenderScreen = true;
    }
  }
}

void InventoryScreen::update()
{
}

void InventoryScreen::render()
{
  if (mRenderScreen) {
    if (mState == States::SHOW_LIST) {
      showEquipment();
      showInventory();
    }
    else if (mState == States::SHOW_ITEM) {
      showItem(mCurrentItemIndex);
    }

    mRenderScreen = false;
  }
}