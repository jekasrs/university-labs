#include <iostream>

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

int main(){
  try{
  point_t point1{4,-3};
  Rectangle rectangle({2.2,5, point1});
  Circle circle(2, point1);

  Shape* shaper = &rectangle;
  shaper->print();
  Shape* shapec = &circle;
  shapec->print();

  std::cout << "Rectangle area=" << shaper->getArea() << "\n";
  std::cout << "Circle area=" << shapec->getArea() << "\n";

  std::cout << "Move circle on {2,2}" << "\n";
  shapec->move(2,2);
  shapec->print();

  std::cout << "Move rectangle on {1,20}" << "\n";
  shaper->move(1,20);
  shaper->print();

  std::cout << "Square in which the circle will fit is" << "\n";
  Rectangle r = shapec->getFrameRect();
  r.print();
  }
  catch (const std::exception& ex){
    std::cerr << ex.what() << '\n';
    return 1;
  }
  return 0;
}
