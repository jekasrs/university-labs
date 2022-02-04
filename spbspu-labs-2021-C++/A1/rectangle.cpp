#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(const rectangle_t &rectangle):
  data(rectangle)
{
  if (data.width <= 0.0){
    throw std::invalid_argument("Width side must be positive");
  }
  if (data.height <= 0.0){
    throw std::invalid_argument("Height side must be positive");
  }
}

double Rectangle::getArea() const
{
  return data.width * data.height;
}

void Rectangle::move(const point_t &newPoint)
{
  data.pos = newPoint;
}

void Rectangle::move(const double dx, const double dy)
{
  data.pos.x += dx;
  data.pos.y += dy;
}

rectangle_t Rectangle::getFrameRect() const
{
  return data;
}

void Rectangle::print() const
{
  std::cout << "About arguments rect:\n"
            << "Centre: {" << data.pos.x << ","
            << data.pos.y << "}\n"
            << "Width = " << data.width << '\n'
            << "Height = " << data.height << '\n';
}
