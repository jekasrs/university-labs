#include <iostream>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <string>
#include "tasks.hpp"

void B5::task1()
{
  std::unordered_set<std::string> palabras((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());
  if (!std::cin.eof())
  {
    throw std::invalid_argument("Reading failed!\n");
  }
  std::copy(palabras.begin(), palabras.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
