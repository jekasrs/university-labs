#ifndef STREAM_GUARD_HPP
#define STREAM_GUARD_HPP

#include <fstream>

class FileGuard
{
  public:
  FileGuard(const char *fileName);
  FileGuard(const FileGuard&) = delete;
  FileGuard(FileGuard&&) = default;
  ~FileGuard();

  FileGuard& operator=(const FileGuard&) = delete;
  FileGuard& operator=(FileGuard&&) = delete;

  std::ifstream fileStream;
};
#endif
