#include <iostream>
#include <exception>
#include <cstring>
#include <string>

#include "tasks.hpp"

int main (int argc, char* argv[])
{
  try
  {
    if(argc < 2 || argc > 4)
    {
      throw std::invalid_argument("Error! Input invalid argument: " + std::to_string(argc));
    }

    for (const char s: std::string(argv[1]))
    {
      if (s < '0' || s > '9')
      {
        throw std::invalid_argument("Error! Invalid task number"+'\n');
      }
    }
    int numberTask = atoi(argv[1]);

    if(numberTask < 1 || numberTask > 4)
    {
      throw:: std::invalid_argument("Error! Task number is between from 1 and 4 - not "
        + std::to_string(numberTask) + '\n');
    }

    switch (numberTask)
    {
      case 1:
        if(argc != 3)
        {
          throw std::invalid_argument("Error! Invalid amount of input parameters, must be 3 - not "
            + std::to_string(argc) + '\n');
        }
        if (std::strcmp(argv[2],"ascending") && std::strcmp(argv[2],"descending"))
        {
          throw std::invalid_argument("Error! Invalid sort direction");
        }
        firstTask(argv[2]);
        break;

      case 2:
        if(argc != 3)
        {
          throw std::invalid_argument("Error! Invalid amount of input parameters, must be 3 - not "
            + std::to_string(argc) + '\n');
        }
        secondTask(argv[2]);
        break;

      case 3:
        if(argc != 2)
        {
          throw std::invalid_argument("Error! Invalid amount of input parameters, must be 2 - not "
            + std::to_string(argc) + '\n');
        }
        thirdTask();
        break;

      case 4:
        if(argc != 4)
        {
          throw std::invalid_argument("Error! Invalid amount of input parameters, must be 4 - not"
            + std::to_string(argc) + '\n');
        }
        if (std::strcmp(argv[2],"ascending") && std::strcmp(argv[2],"descending"))
        {
          throw std::invalid_argument("Error! Invalid sort direction");
        }
        for (const char s: std::string(argv[3]))
        {
          if (s < '0' || s > '9')
          {
            throw std::invalid_argument("Error! Invalid amount of random numbers"+'\n');
          }
        }
        fourthTask(argv[2], atoi(argv[3]));
        break;

      default:{}
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error\n";
    return 2;
  }
  return 0;
}
