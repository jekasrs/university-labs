#include "tasks.hpp"

#include <vector>
#include <memory>
#include <fstream>

#include "streamguard.hpp"
#include "utilities.hpp"

void secondTask(const char *file)
{
  typedef std::unique_ptr<char[], decltype(&free)> bufferType;

  FileGuard fin (file);
  if (!fin.fileStream.is_open())
  {
    throw std::ios_base::failure("File cannot be open! Task 2");
  }
  if (fin.fileStream.peek() == EOF)
  {
    return;
  }
  size_t index = 0;
  size_t size = 32;
  bufferType data(static_cast<char*>(malloc(size)),&free);
  if (!data || data == nullptr)
  {
    throw std::bad_alloc();
  }

  fin.fileStream >> data[index];

  while (fin.fileStream)
  {
    index++;
    if (index == size)
    {
      size = 2*size;
      bufferType tempData(static_cast<char*>(realloc(data.get(),size)),&std::free);
      if (!tempData || tempData == nullptr)
      {
        throw std::runtime_error("Can't reallocate memory");
      }
      std::swap(data,tempData);
      tempData.release();
    }
    fin.fileStream >> data[index];
  }

  if (!fin.fileStream.good() && !fin.fileStream.eof())
  {
    throw std::ios_base::failure("Reading data has failed! Task 2");
  }
  std::vector<char> vector(&data[0], &data[index]);
  utilities::print(vector);
}
