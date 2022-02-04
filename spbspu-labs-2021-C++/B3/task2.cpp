#include <iostream>
#include <algorithm>

#include "FactorialContainer.hpp"

void task2()
{
  factorial::FactorialContainer container;
  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
  std::copy(container.rbegin(), container.rend(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
