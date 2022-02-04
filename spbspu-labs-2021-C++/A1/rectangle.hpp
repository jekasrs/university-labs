#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t& rectangle);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& newPoint) override;
  void move(double dx, double dy) override;
  void print() const override;
private:
  rectangle_t data;
};

#endif
