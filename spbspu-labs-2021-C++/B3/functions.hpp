#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <functional>
#include <sstream>
#include "PhoneBookInterface.hpp"

namespace userFunctions
{
  std::function<void(telephonebook::PhoneBookInterface&)> addRecord(std::istream&);
  std::function<void(telephonebook::PhoneBookInterface&)> storeMark(std::istream&);
  std::function<void(telephonebook::PhoneBookInterface&)> insertRecord(std::istream&);
  std::function<void(telephonebook::PhoneBookInterface&)> deleteMark(std::istream&);
  std::function<void(telephonebook::PhoneBookInterface&)> showMark(std::istream&);
  std::function<void(telephonebook::PhoneBookInterface&)> moveMark(std::istream&);

  std::string parserCommand(std::istream&);

  using command = std::function<std::function<void(telephonebook::PhoneBookInterface&)>(std::istream&)>;
  static const std::map<std::string, command>
  listOfCommands =
  {
    {"add", addRecord},
    {"store", storeMark},
    {"insert", insertRecord},
    {"delete", deleteMark},
    {"show",  showMark},
    {"move",  moveMark}
  };
}
#endif
