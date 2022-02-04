#ifndef POINT_HPP
#define POINT_HPP

#include <iosfwd>
namespace smirnov
{
  struct Point
  {
    int x;
    int y;
  };

  std::istream& operator>>(std::istream&, Point&);
  std::ostream& operator<<(std::ostream&, const Point&);

  char readSymbol(std::istream&);
  std::istream& myskipws(std::istream&);
  double findDistance(const Point&, const Point&);
}
#endif
