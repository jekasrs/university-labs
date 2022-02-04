#include <stdexcept>
#include "FactorialContainer.hpp"

#define INCORRECT_INDEX "Incorrect index! Index could be from 1 to 11!\n"

factorial::FactorialContainer::Iterator::Iterator():
  index_(firstIndex),
  factorial_(currentIndex)
{}

factorial::FactorialContainer::Iterator::Iterator(unsigned int index):
  index_(index)
{
  if (index < firstIndex || index > lastIndex)
  {
    throw std::out_of_range(INCORRECT_INDEX);
  }

  unsigned int value = currentIndex;
  for (unsigned int i = firstIndex; i <= index; ++i)
  {
    value *= i;
  }
  factorial_ = value;
}

unsigned int factorial::FactorialContainer::Iterator::operator*() const
{
  return factorial_;
}

bool factorial::FactorialContainer::Iterator::operator==(const Iterator& rhs) const
{
  return index_ == rhs.index_;
}

bool factorial::FactorialContainer::Iterator::operator!=(const Iterator& rhs) const
{
  return !(index_ == rhs.index_);
}

factorial::FactorialContainer::FactorialContainer::Iterator& factorial::FactorialContainer::Iterator::operator++()
{
  if (index_ + 1 > lastIndex)
  {
    throw std::out_of_range(INCORRECT_INDEX);
  }
  ++index_;
  factorial_ *= index_;
  return *this;
}

factorial::FactorialContainer::Iterator factorial::FactorialContainer::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

factorial::FactorialContainer::Iterator& factorial::FactorialContainer::Iterator::operator--()
{
  if (index_ - 1 < firstIndex)
  {
    throw std::out_of_range(INCORRECT_INDEX);
  }
  factorial_ /= index_;
  --index_;
  return *this;
}

factorial::FactorialContainer::Iterator factorial::FactorialContainer::Iterator::operator--(int)
{
  Iterator temp = *this;
  --(*this);
  return temp;
}

factorial::FactorialContainer::Iterator factorial::FactorialContainer::begin() const
{
  return Iterator(FactorialContainer::Iterator::firstIndex);
}

factorial::FactorialContainer::Iterator factorial::FactorialContainer::end() const
{
  return Iterator(FactorialContainer::Iterator::lastIndex);
}

factorial::FactorialContainer::FactorialContainer::ReversIterator factorial::FactorialContainer::rbegin() const
{
  return std::make_reverse_iterator(end());
}

factorial::FactorialContainer::FactorialContainer::ReversIterator factorial::FactorialContainer::rend() const
{
  return std::make_reverse_iterator(begin());
}
