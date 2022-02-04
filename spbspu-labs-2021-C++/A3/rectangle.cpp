#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>

smirnov::Rectangle::Rectangle(const rectangle_t &rectangle):
  data(rectangle)
{
  if (data.width <= 0.0)
  {
    throw std::invalid_argument("Width side must be positive\n");
  }
  if (data.height <= 0.0)
  {
    throw std::invalid_argument("Height side must be positive\n");
  }
}

double smirnov::Rectangle::getArea() const noexcept
{
  return data.width * data.height;
}

void smirnov::Rectangle::move(const point_t &newPoint) noexcept
{
  data.pos = newPoint;
}

void smirnov::Rectangle::move(const double dx, const double dy) noexcept
{
  data.pos.x += dx;
  data.pos.y += dy;
}

smirnov::rectangle_t smirnov::Rectangle::getFrameRect() const
{
  return data;
}

void smirnov::Rectangle::print(std::ostream& out) const
{
  out << "About arguments rect:\n"
      << "Centre: {" << data.pos.x << ","
      << data.pos.y << "}\n"
      << "Width:" << data.width << '\n'
      << "Height:" << data.height << '\n'
      << "Area:" << getArea() << '\n';
}

void smirnov::Rectangle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("Incorrect coefficient!\n");
  }
  data.width *= k;
  data.height *= k;
}

smirnov::point_t smirnov::Rectangle::getCenter() const noexcept
{
  return data.pos;
}
