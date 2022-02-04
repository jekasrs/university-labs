#include "tasks.hpp"

#include <vector>
#include <forward_list>

#include "utilities.hpp"

void firstTask(const char *direction)
{
  std::vector<int> vectorIndex;
  int in;

  while (std::cin >> in)
  {
    if (std::cin.fail())
    {
      throw std::invalid_argument("Invalid data! Task 1");
    }
    vectorIndex.push_back(in);
  }

  if (!std::cin.eof() && !std::cin.good())
  {
    throw std::ios_base::failure("Reading data has failed! Task 1");
  }

  if (vectorIndex.empty())
  {
    return;
  }

  std::vector<int> vectorAt(vectorIndex);
  std::forward_list<int> list(vectorIndex.begin(), vectorIndex.end());

  std::function<bool(int,int)> compare = utilities::directionType<int>(direction);

  utilities::bubbleSort<IndexConteiner>(vectorIndex, compare);
  utilities::print(vectorIndex, " ");

  utilities::bubbleSort<AtConteiner>(vectorAt, compare);
  utilities::print(vectorAt, " ");

  utilities::bubbleSort<IteratorConteiner>(list, compare);
  utilities::print(list, " ");
}
