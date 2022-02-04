#include "circle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>


smirnov::Circle::Circle(const double &radius, const point_t &center):
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Radius must be positive\n");
  }
}

double smirnov::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

void smirnov::Circle::move(const point_t &pos) noexcept
{
  center_ = pos;
}

void smirnov::Circle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

smirnov::rectangle_t smirnov::Circle::getFrameRect() const
{
  return smirnov::rectangle_t{ 2 * radius_, 2 * radius_, center_};
}

void smirnov::Circle::print(std::ostream& out) const
{
  out << "About arguments circle:\n"
      << "Centre: {" << center_.x << ","
      << center_.y << "}\n"
      << "Radius = " << radius_ << '\n'
      << "Area:" << getArea() << '\n';
}

void smirnov::Circle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("Incorrect coefficient!\n");
  }
  radius_ *= k;
}

smirnov::point_t smirnov::Circle::getCenter() const noexcept
{
  return this->center_;
}
