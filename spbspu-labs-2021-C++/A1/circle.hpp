#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const double &radius, const point_t &center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &newPoint) override;
  void move(double dx, double dy) override;
  void print() const override;
private:
  point_t center_;
  double radius_;
};

#endif
