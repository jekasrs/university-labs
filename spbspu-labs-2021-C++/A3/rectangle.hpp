#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED

#include <iostream>
#include "shape.hpp"

namespace smirnov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t& rectangle);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPoint) noexcept override;
    void move(double dx, double dy) noexcept override;
    void print(std::ostream& out) const override;
    void scale(double k) override;
    point_t getCenter() const noexcept override;
  private:
    rectangle_t data;
  };
}
#endif
