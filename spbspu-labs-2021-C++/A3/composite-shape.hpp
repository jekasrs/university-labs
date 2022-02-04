#ifndef COMPOSITE_SHAPE_HPP_INCLUDEDS
#define COMPOSITE_SHAPE_HPP_INCLUDEDS

#include <memory>
#include "shape.hpp"
#include "base-types.hpp"

namespace smirnov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape() noexcept;
    CompositeShape(const std::shared_ptr<Shape>& shape);
    CompositeShape(const CompositeShape& compositeShape);
    CompositeShape(CompositeShape&& compositeShape) = default;
    ~CompositeShape() = default;

    CompositeShape& operator=(const CompositeShape& compositeShape);
    CompositeShape& operator=(CompositeShape&& compositeShape) = default;
    std::shared_ptr<Shape> operator[](int index);
    const std::shared_ptr<Shape> operator[](int index) const;

    double getArea() const noexcept override;
    void move(const point_t& point) noexcept override;
    void move(double dx, double dy) noexcept override;
    void scale(double coefficient) override;
    void print(std::ostream& out) const override;
    rectangle_t getFrameRect() const override;

    point_t getCenter() const;
    int getNumberOfShapes() const noexcept;

    void pushBack(const std::shared_ptr<Shape>& newShape);
    void popBack();

    void pushAhead(const std::shared_ptr<Shape>& newShape);
    void popAhead();

    void insert(const std::shared_ptr<Shape>& newShape, const int index);
    void remove(const int index);

  private:
    int capacity_;
    int size_;
    std::unique_ptr<std::shared_ptr<Shape>[]> arrayOfShapes_;
  };
}
#endif
