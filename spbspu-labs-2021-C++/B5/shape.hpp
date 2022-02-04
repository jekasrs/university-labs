#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <iosfwd>
#include "point.hpp"

namespace smirnov
{
  using Shape = std::vector<Point>;

  std::istream& operator>>(std::istream&, Shape&);
  std::ostream& operator<<(std::ostream&, const Shape&);

  bool isSquare(const Shape& shape);
  bool isTriangle(const Shape& shape);
  bool isRectangle(const Shape& shape);
  bool compareShapes(const Shape& lhs, const Shape& rhs);
}
#endif
