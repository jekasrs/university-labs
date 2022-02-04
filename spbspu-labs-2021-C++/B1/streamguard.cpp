#include "streamguard.hpp"
#include <iostream>

FileGuard::FileGuard(const char *fileName)
{
  fileStream.open(fileName);
}

FileGuard::~FileGuard()
{
  fileStream.close();
}
