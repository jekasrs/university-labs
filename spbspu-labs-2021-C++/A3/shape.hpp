#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include <iostream>
#include "base-types.hpp"

namespace smirnov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& point) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void scale(double k) = 0;
    virtual point_t getCenter() const = 0;
  };
}
#endif
