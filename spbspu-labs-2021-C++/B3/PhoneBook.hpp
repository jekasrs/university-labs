#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <list>
#include "PhoneNote.hpp"

namespace telephonebook
{
  class PhoneBook
  {
  public:
    using iterator = std::list<PhoneNote>::iterator;

    void pushBack(const PhoneNote& note);
    void pushFront(const PhoneNote& note);
    void show(iterator it) const;
    bool isEmpty() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    iterator insertAfter(iterator it, const PhoneNote& note);
    iterator insertBefore(iterator it, const PhoneNote& note);
    iterator deleteNote(iterator it);
    iterator replace(const PhoneNote& note, iterator it);

  private:
    std::list<PhoneNote> BookList;
  };
}
#endif
