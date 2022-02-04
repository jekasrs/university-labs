#include "checkIn.hpp"
#include <iostream>

bool checker::isNumberCorrect(const std::string& number)
{
  if (number.empty())
  {
    return false;
  }
  for (auto s:number)
  {
    if (!isdigit(s))
    {
      return false;
    }
  }
  return true;
}

bool checker::isMarkNameCorrect(const std::string& bookMark)
{
  if (bookMark.empty())
  {
    return false;
  }
  for(auto s: bookMark)
  {
    if ((isalnum(s) == 0) && (s != '-'))
    {
      return false;
    }
  }
  return true;
}

bool checker::isNameCorrect(const std::string& name)
{
  if (name.front() != '\"' || name.back() != '\"' || name.empty())
  {
    return false;
  }
  return true;
}

void checker::deleteRubish(std::string& name)
{
  name.erase(0, 1);
  name.erase(name.length() - 1, 1);
  for (size_t i = 0; i < name.size(); i++)
  {
    if (name[i] == '\\')
    {
      name.erase(i, 1);
    }
  }
}
