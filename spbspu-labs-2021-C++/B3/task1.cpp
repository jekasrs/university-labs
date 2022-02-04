#include <exception>
#include "PhoneBookInterface.hpp"
#include "functions.hpp"

void task1()
{
  telephonebook::PhoneBookInterface phoneBook(std::make_unique<telephonebook::PhoneBook>(telephonebook::PhoneBook()));
  std::string string;
  while (std::getline(std::cin, string))
  {
    if ((std::cin.fail() || std::cin.bad()) && !std::cin.eof())
    {
      throw std::runtime_error("Error of reading data in task 1!\n");
    }
    std::istringstream istream(string);
    try
    {
      std::string operation = userFunctions::parserCommand(istream);
      userFunctions::listOfCommands.at(operation)(istream)(phoneBook);
    }
    catch(const std::exception& e)
    {
      std::cout << e.what();
    }
  }
}
