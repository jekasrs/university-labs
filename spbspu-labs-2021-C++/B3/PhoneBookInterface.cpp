#include <iostream>

#include "PhoneBookInterface.hpp"

#define INVALID_BOOKMARK "<INVALID BOOKMARK>\n"
#define EMPTY "<EMPTY>\n"

telephonebook::PhoneBookInterface::PhoneBookInterface(ptrBook other)
{
  phoneBook_ = std::move(other);
  bookmarks_.insert(std::make_pair("current", phoneBook_->begin()));
}

void telephonebook::PhoneBookInterface::addRecord(PhoneNote& newRecord)
{
  phoneBook_->pushBack(newRecord);
  if (phoneBook_->begin() == --phoneBook_->end())
  {
    bookmarks_["current"] = phoneBook_->begin();
  }
}

void telephonebook::PhoneBookInterface::storeMark(const std::string& markName, const std::string& newMarkName)
{
  auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }
  auto recordIt = it->second;
  bookmarks_.insert(std::make_pair(newMarkName, recordIt));
}

void telephonebook::PhoneBookInterface::insertBefore(PhoneNote& newRecord, const std::string& markName)
{
  if (markName == "current" && (phoneBook_->begin() == phoneBook_->end()))
  {
    addRecord(newRecord);
  }
  else
  {
    auto it = bookmarks_.find(markName);
    if (it == bookmarks_.end())
    {
      std::cout << INVALID_BOOKMARK;
      return;
    }
    phoneBook_->insertBefore(it->second, newRecord);
    if (bookmarks_.size() == 1)
    {
      bookmarks_["current"] = phoneBook_->begin();
    }
  }
}

void telephonebook::PhoneBookInterface::insertAfter(PhoneNote& newRecord, const std::string& markName)
{
  if (markName == "current" && (phoneBook_->begin() == phoneBook_->end()))
  {
    addRecord(newRecord);
  }
  else
  {
    auto it = bookmarks_.find(markName);
    if (it == bookmarks_.end())
    {
      std::cout << INVALID_BOOKMARK;
      return;
    }
    phoneBook_->insertAfter(it->second, newRecord);
    if (bookmarks_.size() == 1)
    {
      bookmarks_["current"] = phoneBook_->begin();
    }
  }
}

void telephonebook::PhoneBookInterface::showMark(const std::string& markName)
{
  if (bookmarks_.empty())
  {
    std::cout << EMPTY;
    return;
  }
  auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
  }
  else if (phoneBook_->begin() == phoneBook_->end())
  {
    std::cout << EMPTY;
  }
  else
  {
    phoneBook_->show(it->second);
  }
}

void telephonebook::PhoneBookInterface::moveMark(const std::string& markName, const MovePositionKeyWords& pos)
{
  auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }
  if (pos == MovePositionKeyWords::FIRST)
  {
    it->second = phoneBook_->begin();
  }
  else
  {
    it->second = --phoneBook_->end();
  }
}

void telephonebook::PhoneBookInterface::moveMark(const std::string& markName, int step)
{
  auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }
  bool isStepPositive = true;
  if (step < 0)
  {
    step *= -1;
    isStepPositive = false;
  }
  for (int i = 0; i < step; i++)
  {
    if (isStepPositive)
    {
      if (it->second == --phoneBook_->end())
      {
        break;
      }
      it->second++;
    }
    else
    {
      if (it->second == phoneBook_->begin())
      {
        break;
      }
      it->second--;
    }
  }
}

void telephonebook::PhoneBookInterface::deleteRecordOnMark(const std::string& markName)
{
  auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }
  if (it->second == phoneBook_->end())
  {
    return;
  }
  auto deleteIt = it->second;
  for (auto i = bookmarks_.begin(); i != bookmarks_.end(); i++)
  {
    if (i->second == deleteIt)
    {
      if (std::next(i->second) == phoneBook_->end())
      {
        i->second = phoneBook_->begin();
      }
      else
      {
        i->second = std::next(deleteIt);
      }
    }
  }
  phoneBook_->deleteNote(deleteIt);
}
