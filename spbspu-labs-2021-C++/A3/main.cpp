#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

#include <iostream>
#include <exception>
#include <memory>

using namespace smirnov;

void TestComposite();
void TestShape();
void TestAddDelete();

int main()
{
 // TestShape();
 // TestComposite();
  TestAddDelete();
  return 0;
}

void TestShape()
{
  std::cout << "Begin test scale for shape";
  Shape *shape = new Rectangle({9,9,{1,-1}});
  shape->print(std::cout);
  shape->scale(2.5);
  shape->print(std::cout);
  delete shape;
}

void TestComposite()
{
  Rectangle rectangle1({2, 2, {2,-2} });
  Rectangle rectangle2({ 4, 2, {0,-5} });
  Circle circle1(2, {0,5});

  CompositeShape composition;
  composition.pushBack(std::make_shared<Rectangle>(rectangle1));
  composition.pushBack(std::make_shared<Rectangle>(rectangle2));
  composition.pushBack(std::make_shared<Circle>(circle1));
  composition.print(std::cout);

  composition.move({-5,-1});
  composition.print(std::cout);

  CompositeShape compositionCopy = composition;
  compositionCopy.print(std::cout);

  std::cout << "\n Areas of 2 compositions:\n";
  std::cout << compositionCopy.getArea() << "\n";
  std::cout << composition.getArea() << "\n";

  compositionCopy.scale(2);

  std::cout << "Areas of 2 compositions after scaling:\n";
  std::cout << compositionCopy.getArea() << "\n";
  std::cout << composition.getArea() << "\n";

  std::cout << "NumberOfshapes in 2 compositions:\n";
  std::cout << compositionCopy.getNumberOfShapes() << "\n";
  std::cout << composition.getNumberOfShapes() << "\n";

  compositionCopy.popBack();
  compositionCopy.popBack();

  std::cout << "NumberOfshapes in 2 compositions after delete:\n";
  std::cout << compositionCopy.getNumberOfShapes() << "\n";
  std::cout << composition.getNumberOfShapes() << "\n";
}

void TestAddDelete()
{
  Rectangle rectangle1({1, 1, {1,1} });
  Rectangle rectangle2({2, 2, {2,-2} });
  Rectangle rectangle3({3, 3, {3,-3} });
  Rectangle rectangle4({4, 4, {4,-4} });

  CompositeShape composition;
  composition.pushAhead(std::make_shared<Rectangle>(rectangle1));
  composition.pushAhead(std::make_shared<Rectangle>(rectangle2));
  composition.insert(std::make_shared<Rectangle>(rectangle3),0);
  composition.pushBack(std::make_shared<Rectangle>(rectangle4));

  composition[0]->print(std::cout);
  composition[1]->print(std::cout);
  composition[2]->print(std::cout);
  composition[3]->print(std::cout);

  composition.remove(2);
  composition[0]->print(std::cout);
  composition[1]->print(std::cout);
  composition[2]->print(std::cout);
}
