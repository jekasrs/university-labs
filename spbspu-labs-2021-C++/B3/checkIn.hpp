#ifndef CHECK_IN_HPP
#define CHECK_IN_HPP

#include <string>
#include <iosfwd>

namespace checker
{
  bool isNumberCorrect(const std::string& number);
  bool isMarkNameCorrect(const std::string& bookMark);
  bool isNameCorrect(const std::string& name);
  void deleteRubish(std::string& name);
}
#endif
