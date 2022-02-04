#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED

#include <iostream>
#include "shape.hpp"

namespace smirnov
{
  class Circle : public Shape
  {
  public:
    Circle(const double &radius, const point_t &center);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newPoint) noexcept override;
    void move(double dx, double dy) noexcept override;
    void print(std::ostream& out) const override;
    void scale(double k) override;
    point_t getCenter() const noexcept override;
  private:
    point_t center_;
    double radius_;
  };
}
#endif
