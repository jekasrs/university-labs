#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "DataStruct.hpp"

int main()
{
  try
  {
    std::vector<B4::DataStruct> vector((std::istream_iterator<B4::DataStruct>(std::cin)), std::istream_iterator<B4::DataStruct>());
    if (std::cin.fail()&& !std::cin.eof())
    {
      throw std::invalid_argument("Error! Reading failed \n");
    }

    std::sort(vector.begin(), vector.end());
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<B4::DataStruct>(std::cout));
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error" << '\n';
    return 2;
  }
  return 0;
}
