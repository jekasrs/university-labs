#include "tasks.hpp"

#include <vector>

#include "utilities.hpp"

void fourthTask(const char* direction, long size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Size should be > 0! Task 4");
  }
  std::vector<double> vector(size);
  utilities::fillRandom(vector.data(), size);
  utilities::print(vector, " ");
  utilities::bubbleSort<IndexConteiner>(vector,utilities::directionType<double>(direction));
  utilities::print(vector, " ");
}
