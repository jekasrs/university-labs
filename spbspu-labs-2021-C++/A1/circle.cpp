#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <stdexcept>


Circle::Circle(const double &radius, const point_t &center):
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0){
    throw std::invalid_argument("Radius must be positive");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

void Circle::move(const point_t &pos)
{
  center_ = pos;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, center_};
}

void Circle::print() const
{
  std::cout << "About arguments circle:\n"
            << "Centre: {" << center_.x << ","
            << center_.y << "}\n"
            << "Radius = " << radius_ << '\n';
}
