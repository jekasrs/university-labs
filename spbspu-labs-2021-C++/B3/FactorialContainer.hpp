#ifndef FACTORIAL_CONTAINER
#define FACTORIAL_CONTAINER

#include <iterator>

namespace factorial
{
  class FactorialContainer
  {
  public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t, std::ptrdiff_t, size_t*, size_t>
    {
    public:
      static const unsigned int firstIndex = 1;
      static const unsigned int lastIndex = 11;

      Iterator();
      Iterator(unsigned int index);

      unsigned int operator*() const;
      bool operator==(const Iterator& rhs) const;
      bool operator!=(const Iterator& rhs) const;
      Iterator& operator++();
      Iterator operator++(int);
      Iterator& operator--();
      Iterator operator--(int);

    private:
      unsigned int currentIndex = 1;
      unsigned int index_;
      unsigned int factorial_;
    };

    Iterator begin() const;
    Iterator end() const;

    using ReversIterator = std::reverse_iterator<Iterator>;
    ReversIterator rbegin() const;
    ReversIterator rend() const;
  };
}
#endif
