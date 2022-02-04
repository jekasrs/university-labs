#include <iostream>
#include <string>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2 || std::string(argv[1]).length()!=1)
    {
      throw std::invalid_argument("Incorrect number of arguments!\n");
    }
    int task = std::stoi(argv[1]);

    switch (task)
    {
      case 1:
        B5::task1();
        break;
      case 2:
        B5::task2();
        break;
      default:
        throw std::invalid_argument("Error! Invalid task number:"
              + std::to_string(task) + " Must be 1 or 2!\n");
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
