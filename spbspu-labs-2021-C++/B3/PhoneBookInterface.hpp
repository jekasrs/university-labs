#ifndef PHONE_BOOK_INTERFACE_HPP
#define PHONE_BOOK_INTERFACE_HPP

#include <memory>
#include <map>

#include "PhoneBook.hpp"
namespace telephonebook
{
  class PhoneBookInterface
  {
  public:
  enum class MovePositionKeyWords
  {
    FIRST,
    LAST,
  };

  using ptrBook = std::unique_ptr<PhoneBook>;
  PhoneBookInterface(ptrBook interfaceBook);
  PhoneBookInterface(PhoneBookInterface&&) = default;
  PhoneBookInterface(const PhoneBookInterface&) = delete;
  ~PhoneBookInterface() = default;

  PhoneBookInterface& operator=(const PhoneBookInterface&) = delete;
  PhoneBookInterface& operator=(PhoneBookInterface&&) = default;

  void addRecord(PhoneNote& newRecord);
  void storeMark(const std::string& markName, const std::string& newMarkName);
  void insertBefore(PhoneNote& newRecord, const std::string& markName);
  void insertAfter(PhoneNote& newRecord, const std::string& markName);
  void deleteRecordOnMark(const std::string& markName);
  void showMark(const std::string& markName);
  void moveMark(const std::string& markName, int step);
  void moveMark(const std::string& markName, const MovePositionKeyWords& pos);

  private:
  ptrBook phoneBook_;
  std::map<std::string, PhoneBook::iterator> bookmarks_;
  };
}
#endif
