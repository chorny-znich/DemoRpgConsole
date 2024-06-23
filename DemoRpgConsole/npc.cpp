#include <string>
#include <format>
#include "npc.h"

void Npc::addStaff(std::shared_ptr<GameObject> object)
{
  mStaff.push_back(std::move(object));
}

std::vector<std::shared_ptr<GameObject>>& Npc::getStaff()
{
  return mStaff;
}

size_t Npc::getStaffSize() const
{
  return mStaff.size();
}

std::string Npc::showStaff() const
{
  std::string result{};
  result.append("\nItems for sale:\n");
  if (mStaff.size() == 0) {
    return result.append("There is nothing for sale");
  }
  size_t counter{ 1 };
  for (auto pObject : mStaff) {
    result.append(std::format("{}. {} -- ${}\n", counter++, pObject->getName(), pObject->getPrice()));
  }

  return result;
}

void Npc::removeFromStaff(size_t index)
{
  mStaff.erase(mStaff.begin() + index);
}
