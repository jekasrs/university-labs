#include <iostream>
#include <string>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Error! Invalid number of arguments!\n");
    }

    if (std::string(argv[1]).length() > 1)
    {
      throw std::invalid_argument("Error! Invalid task number!\n");
    }

    int numberOfTask = std::stoi(argv[1]);
    switch (numberOfTask)
    {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    default:
      throw std::invalid_argument("Error! Invalid task number: " +
            std::to_string(numberOfTask) + " Must be 1 or 2!\n");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!\n";
    return 2;
  }
  return 0;
}
