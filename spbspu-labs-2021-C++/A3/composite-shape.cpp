#include "composite-shape.hpp"

#include <cmath>
#include <exception>
#include <iostream>

smirnov::CompositeShape::CompositeShape() noexcept :
  capacity_(0),
  size_(0),
  arrayOfShapes_(nullptr)
{}

smirnov::CompositeShape::CompositeShape(const std::shared_ptr<Shape>& shape) :
  capacity_(1),
  size_(1),
  arrayOfShapes_(std::make_unique<std::shared_ptr<Shape>[]>(1))
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Try to add invalid shape!\n");
  }
  arrayOfShapes_[0] = shape;
}

smirnov::CompositeShape::CompositeShape(const CompositeShape& rcomposit) :
  capacity_(rcomposit.capacity_),
  size_(rcomposit.size_),
  arrayOfShapes_(std::make_unique<std::shared_ptr<Shape>[]>(rcomposit.size_))
{
  std::unique_ptr<std::shared_ptr<Shape>[]> tempArray(std::make_unique<std::shared_ptr<Shape>[]>(rcomposit.size_));

  for(int i = 0; i < rcomposit.size_; i++)
  {
    std::shared_ptr<smirnov::Shape> tempShape = rcomposit.arrayOfShapes_[i];
    tempArray[i] = tempShape;
  }
  arrayOfShapes_ = std::move(tempArray);
}

smirnov::CompositeShape& smirnov::CompositeShape::operator=(const CompositeShape& rcomposit)
{
  if (this != &rcomposit)
  {
    smirnov::CompositeShape temp(rcomposit);
    *this = std::move(temp);
  }
  return *this;
}

const std::shared_ptr<smirnov::Shape> smirnov::CompositeShape::operator[](int index) const
{
  if (index < 0 || index >= size_)
  {
    throw std::out_of_range("Index is out of range!\n");
  }
  return arrayOfShapes_[index];
}

std::shared_ptr<smirnov::Shape> smirnov::CompositeShape::operator[](int index)
{
  if (index < 0 || index >= size_)
  {
    throw std::out_of_range("Index is out of range!\n");
  }
  return arrayOfShapes_[index];
}

double smirnov::CompositeShape::getArea() const noexcept
{
  double area = 0.0;
  for (int i = 0; i < size_; i++)
  {
    area += arrayOfShapes_[i]->getArea();
  }
  return area;
}

int smirnov::CompositeShape::getNumberOfShapes() const noexcept
{
  return size_;
}

void smirnov::CompositeShape::print(std::ostream& out) const
{
  if (size_ == 0)
  {
    out << "Nothing to watch! Composit is empty! \n";
  }
  else
  {
    out << "Height of frame: " << getFrameRect().height <<"\n"
        << "Width of frame: " << getFrameRect().width <<"\n"
        << "Center: (" << getCenter().x << "; " << getCenter().y << ")\n"
        << "Area: " << getArea() <<"\n"
        << "Number of shapes: " << size_ <<"\n";
  }
}

smirnov::rectangle_t smirnov::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    throw std::underflow_error("Composite shape is empty!\n");
  }
  rectangle_t frameRec = arrayOfShapes_[0]->getFrameRect();

  double upLeftX = frameRec.pos.x - frameRec.width / 2.0;
  double upLeftY = frameRec.pos.y + frameRec.height / 2.0;
  double downRightX = frameRec.pos.x + frameRec.width / 2.0;
  double downRightY = frameRec.pos.y - frameRec.height / 2.0;

  point_t left_down = { upLeftX, upLeftY };
  point_t right_up = { downRightX, downRightY };

  for (int i = 1; i < size_; i++)
  {
    frameRec = arrayOfShapes_[i]->getFrameRect();

    upLeftX = frameRec.pos.x - frameRec.width / 2;
    upLeftY = frameRec.pos.y + frameRec.height / 2;

    downRightX = frameRec.pos.x + frameRec.width / 2;
    downRightY = frameRec.pos.y - frameRec.height / 2;

    left_down.x = std::min(upLeftX,left_down.x);
    right_up.y = std::min(downRightY,right_up.y);
    left_down.y = std::max(upLeftY,left_down.y);
    right_up.x = std::max(downRightX,right_up.x);
  }
  return {right_up.x - left_down.x, left_down.y - right_up.y,
    (left_down.x + right_up.x) / 2, (left_down.y + right_up.y) / 2};
}

void smirnov::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Wrong coefficient!\n");
  }
  else if (size_ == 0)
  {
    throw std::logic_error("Nothing to scale!\n");
  }
  const rectangle_t fullFrameRec = getFrameRect();

  for (int i = 0; i < size_; i++)
  {
    arrayOfShapes_[i]->scale(coefficient);
    const rectangle_t tempRect = arrayOfShapes_[i]->getFrameRect();
    const double newX = tempRect.pos.x + coefficient * (tempRect.pos.x - fullFrameRec.pos.x);
    const double newY = tempRect.pos.y + coefficient * (tempRect.pos.y - fullFrameRec.pos.y);
    arrayOfShapes_[i]->move({ newX, newY });
  }
}

void smirnov::CompositeShape::pushBack(const std::shared_ptr<Shape>& newShape)
{
  insert(newShape,size_);
}

void smirnov::CompositeShape::pushAhead(const std::shared_ptr<Shape>& newShape)
{
  insert(newShape,0);
}

void smirnov::CompositeShape::insert(const std::shared_ptr<Shape>& newShape, const int index)
{
  if (newShape == nullptr)
  {
    throw std::logic_error("It is bad idea to add nullptr!\n");
  }

  if (index > size_)
  {
    throw std::out_of_range("It is bad idea to add out of range!\n");
  }

  if (capacity_ == size_)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> tempArray(std::make_unique<std::shared_ptr<Shape>[]>(capacity_*2 + 1));

    capacity_ = capacity_*2 + 1;
    for (int i = 0; i < index; i++)
    {
      tempArray[i] = arrayOfShapes_[i];
    }

    tempArray[index] = newShape;

    for (int i = index+1; i < size_+1; i++)
    {
      tempArray[i] = arrayOfShapes_[i-1];
    }
    size_++;
    arrayOfShapes_ = std::move(tempArray);
  }
  else
  {
    std::shared_ptr<smirnov::Shape> tempShape1 = arrayOfShapes_[index];
    std::shared_ptr<smirnov::Shape> tempShape2;
    arrayOfShapes_[index] = newShape;
    size_++;
    for (int i = index+1; i < size_-2; i++)
    {
      tempShape2 = arrayOfShapes_[i];
      arrayOfShapes_[i] = tempShape1;
      tempShape1 = tempShape2;
    }
    arrayOfShapes_[size_-1] = tempShape1;
  }
}

void smirnov::CompositeShape::popAhead()
{
  remove(0);
}

void smirnov::CompositeShape::popBack()
{
  remove(size_-1);
}

void smirnov::CompositeShape::remove(const int index)
{
  if (size_ == 0)
  {
    throw std::underflow_error("Array of shapes is empty!\n");
  }

  if (index >= size_ || index < 0)
  {
    throw std::out_of_range("The index less size!\n");
  }

  for (int i = index; i < size_-1; i++)
  {
    arrayOfShapes_[i] = arrayOfShapes_[i + 1];
  }
  size_--;
  arrayOfShapes_[size_].reset();
}

void smirnov::CompositeShape::move(double dx, double dy) noexcept
{
  for (int i = 0; i < size_; i++)
  {
    arrayOfShapes_[i]->move(dx, dy);
  }
}

void smirnov::CompositeShape::move(const point_t& point) noexcept
{
  point_t center = getCenter();
  move(point.x - center.x, point.y - center.y);
}

smirnov::point_t smirnov::CompositeShape::getCenter() const
{
  if (size_ == 0)
  {
    throw std::underflow_error("Composite Shape is empty\n");
  }
  return this->getFrameRect().pos;
}
