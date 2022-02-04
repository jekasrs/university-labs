#include <stdexcept>
#include <functional>
#include <iomanip>
#include <sstream>

#include "checkIn.hpp"
#include "functions.hpp"

#define INVALID_COMMAND "<INVALID COMMAND>\n"
#define INVALID_STEP "<INVALID STEP>\n"

std::string userFunctions::parserCommand(std::istream& istream)
{
  std::string operation;
  istream >> operation;
  if (userFunctions::listOfCommands.find(operation) != userFunctions::listOfCommands.end())
  {
    return operation;
  }
  else if (operation != "")
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

std::function<void(telephonebook::PhoneBookInterface&)> userFunctions::addRecord(std::istream& istream)
{
  std::string number, name;
  istream >> std::ws >> number;
  std::getline(istream >> std::ws, name);
  if (!checker::isNameCorrect(name) || !checker::isNumberCorrect(number))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  checker::deleteRubish(name);
  if (name.empty())
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  return [name, number](telephonebook::PhoneBookInterface& phoneBook)
  {
    telephonebook::PhoneNote newRecord(number, name);
    phoneBook.addRecord(newRecord);
  };
}

std::function<void(telephonebook::PhoneBookInterface&)> userFunctions::storeMark(std::istream& istream)
{
  std::string markName, newMarkName;
  istream >> std::ws >> markName;
  istream >> std::ws >> newMarkName;
  if (!istream.eof() || !checker::isMarkNameCorrect(markName)||
      !checker::isMarkNameCorrect(newMarkName))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  return [markName, newMarkName](telephonebook::PhoneBookInterface& phoneBook)
  {
    phoneBook.storeMark(markName, newMarkName);
  };
}

std::function<void(telephonebook::PhoneBookInterface&)> userFunctions::insertRecord(std::istream& istream)
{
  std::string position, markName, number, name;
  istream >> std::ws >> position;
  istream >> std::ws >> markName;
  istream >> std::ws >> number;
  std::getline(istream >> std::ws, name);
  if ((position != "before" && position != "after") ||
       !checker::isNameCorrect(name)||
       !checker::isMarkNameCorrect(markName)||
       !checker::isNumberCorrect(number))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  checker::deleteRubish(name);
  if (name.empty())
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }

  if (position == "before")
  {
    return [number, name, markName](telephonebook::PhoneBookInterface& phoneBook)
    {
      telephonebook::PhoneNote newRecord(number, name);
      phoneBook.insertBefore(newRecord, markName);
    };
  }
  else
  {
    return [number, name, markName](telephonebook::PhoneBookInterface& phoneBook)
    {
      telephonebook::PhoneNote newRecord(number, name);
      phoneBook.insertAfter(newRecord, markName);
    };
  }
}

std::function<void(telephonebook::PhoneBookInterface&)> userFunctions::deleteMark(std::istream& istream)
{
  std::string markName;
  istream >> std::ws >> markName;
  if (!checker::isMarkNameCorrect(markName))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  return [markName](telephonebook::PhoneBookInterface& phoneBook)
  {
    phoneBook.deleteRecordOnMark(markName);
  };
}

std::function<void(telephonebook::PhoneBookInterface&)> userFunctions::showMark(std::istream& istream)
{
  std::string markName;
  istream >> std::ws >> markName;
  if (!checker::isMarkNameCorrect(markName))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  return [markName](telephonebook::PhoneBookInterface& phoneBook)
  {
    phoneBook.showMark(markName);
  };
}

std::function<void(telephonebook::PhoneBookInterface&)> userFunctions::moveMark(std::istream& istream)
{
  std::string markName, steps;
  istream >> std::ws >> markName;
  if (!checker::isMarkNameCorrect(markName))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  istream >> std::ws >> steps;
  int sign = 1;
  if (steps != "first" && steps != "last")
  {
    if (steps[0] == '-')
    {
      sign = -1;
      steps.erase(steps.begin());
    }
    else if (steps[0] == '+')
    {
      steps.erase(steps.begin());
    }
    if (!checker::isNumberCorrect(steps))
    {
      throw std::invalid_argument(INVALID_STEP);
    }
  }
  if (steps == "first")
  {
    telephonebook::PhoneBookInterface::MovePositionKeyWords pos =
    telephonebook::PhoneBookInterface::MovePositionKeyWords::FIRST;
    return [markName, pos](telephonebook::PhoneBookInterface& phoneBook)
    {
      phoneBook.moveMark(markName, pos);
    };
  }
  else if (steps == "last")
  {
    telephonebook::PhoneBookInterface::MovePositionKeyWords pos =
    telephonebook::PhoneBookInterface::MovePositionKeyWords::LAST;
    return [markName, pos](telephonebook::PhoneBookInterface& phoneBook)
    {
      phoneBook.moveMark(markName, pos);
    };
  }
  else
  {
    return [markName, steps, sign](telephonebook::PhoneBookInterface& phoneBook)
    {
      phoneBook.moveMark(markName,(std::stoi(steps) * sign));
    };
  }
}
