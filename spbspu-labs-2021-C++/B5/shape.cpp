#include <iostream>
#include <iterator>
#include "shape.hpp"

std::istream& smirnov::operator>>(std::istream& in, Shape& shape)
{
  std::istream::sentry sin(in);
  if (!sin)
  {
    in.setstate(std::istream::failbit);
    return in;
  }

  int countOfPoints = 0;
  Shape tempShape;

  if (!(in >> countOfPoints))
  {
    in.setstate(std::istream::failbit);
    return in;
  }

  for (int i = 0; i < countOfPoints; i++)
  {
    Point point{0, 0};
    if (in.peek()=='\n')
    {
      in.setstate(std::istream::failbit);
      return in;
    }
    in >> point;
    if (!sin)
    {
      in.setstate(std::istream::failbit);
      return in;
    }
    tempShape.push_back(point);
  }
  if (sin)
  {
    shape = std::move(tempShape);
  }
  return in;
}

std::ostream& smirnov::operator<<(std::ostream& out, const Shape& shape)
{
  std::ostream::sentry sot(out);
  if (sot)
  {
    out << shape.size() << " ";
    std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(out, " "));
  }
  return out;
}

bool smirnov::isTriangle(const Shape& shape)
{
  return shape.size() == 3;
}

bool smirnov::isSquare(const Shape& shape)
{
  if (isRectangle(shape))
  {
    return findDistance(shape[0], shape[1]) == findDistance(shape[1], shape[2]);
  }
  return false;
}

bool smirnov::isRectangle(const Shape& shape)
{
  if (shape.size() == 4)
  {
    return findDistance(shape[0], shape[2]) == findDistance(shape[1], shape[3])
        && findDistance(shape[0], shape[1]) == findDistance(shape[2], shape[3])
        && findDistance(shape[0], shape[3]) == findDistance(shape[1], shape[2]);
  }

  return false;
}

bool smirnov::compareShapes(const Shape& lhs, const Shape& rhs)
{
  if ((lhs.size() == 4) && (rhs.size() == 4))
  {
    if (isSquare(lhs))
    {
      return true;
    }
    if (isSquare(rhs))
    {
      return false;
    }
    return !isRectangle(rhs);
  }
  return lhs.size() < rhs.size();
}
