#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <iterator>
#include "tasks.hpp"
#include "shape.hpp"

void B5::task2()
{
  std::list<smirnov::Shape> shapes{std::istream_iterator<smirnov::Shape>(std::cin), std::istream_iterator<smirnov::Shape>()};
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error! File reading failure!\n");
  }
  size_t verticesAmount  = 0;
  size_t triangleAmount  = 0;
  size_t squaresAmount   = 0;
  size_t rectangleAmount = 0;

  std::for_each(shapes.begin(), shapes.end(),
    [&verticesAmount, &triangleAmount, &squaresAmount, &rectangleAmount](const smirnov::Shape& shape)
    {
      verticesAmount += shape.size();
      if (smirnov::isTriangle(shape))
      {
        triangleAmount++;
      }
      if (smirnov::isRectangle(shape))
      {
        rectangleAmount++;
      }
      if (smirnov::isSquare(shape))
      {
        squaresAmount++;
      }
    });

  std::cout << "Vertices: "   << verticesAmount  << "\n"
            << "Triangles: "  << triangleAmount  << "\n"
            << "Squares: "    << squaresAmount   << "\n"
            << "Rectangles: " << rectangleAmount << "\n";

  shapes.remove_if([](const smirnov::Shape& shape)
    {
      return shape.size() == 5;
    });

  std::vector<smirnov::Point> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const smirnov::Shape& shape)
    {
      return shape[0];
    });

  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<smirnov::Point>(std::cout, " "));
  std::cout << "\n";

  shapes.sort(smirnov::compareShapes);
  std::cout << "Shapes:" << "\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<smirnov::Shape>(std::cout, "\n"));
}
