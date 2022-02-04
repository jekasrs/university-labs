#include "PhoneBook.hpp"

void telephonebook::PhoneBook::pushBack(const PhoneNote& note)
{
  BookList.push_back(note);
}

void telephonebook::PhoneBook::pushFront(const PhoneNote& note)
{
  BookList.push_front(note);
}

void telephonebook::PhoneBook::show(iterator it) const
{
  std::cout << *it;
}

bool telephonebook::PhoneBook::isEmpty() const noexcept
{
  return BookList.empty();
}

telephonebook::PhoneBook::iterator telephonebook::PhoneBook::begin() noexcept
{
  return BookList.begin();
}

telephonebook::PhoneBook::iterator telephonebook::PhoneBook::end() noexcept
{
  return BookList.end();
}

telephonebook::PhoneBook::iterator telephonebook::PhoneBook::insertAfter(PhoneBook::iterator it, const PhoneNote& note)
{
  return BookList.insert(++it, note);
}

telephonebook::PhoneBook::iterator telephonebook::PhoneBook::insertBefore(PhoneBook::iterator it, const PhoneNote& note)
{
  return BookList.insert(it, note);
}

telephonebook::PhoneBook::iterator telephonebook::PhoneBook::deleteNote(iterator it)
{
  if (BookList.empty())
  {
    return BookList.end();
  }
  return BookList.erase(it);
}

telephonebook::PhoneBook::iterator telephonebook::PhoneBook::replace(const PhoneNote& note, iterator it)
{
  it = BookList.erase(it);
  return BookList.insert(it, note);
}
