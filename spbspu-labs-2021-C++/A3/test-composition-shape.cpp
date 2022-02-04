#include <boost/test/unit_test.hpp>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const smirnov::point_t CENTER({0,0});
const double DELTA = 0.001;

BOOST_AUTO_TEST_CASE(composite_shape_constructor_correctness)
{
  const smirnov::Rectangle rectangle({10,2,CENTER});
  const double square = rectangle.getArea();
  const double width = rectangle.getFrameRect().width;
  const double height = rectangle.getFrameRect().height;

  smirnov::CompositeShape cShape(std::make_shared<smirnov::Rectangle>(rectangle));

  BOOST_CHECK_EQUAL(cShape.getCenter().x, CENTER.x);
  BOOST_CHECK_EQUAL(cShape.getCenter().y, CENTER.y);
  BOOST_CHECK_EQUAL(cShape.getFrameRect().width, width);
  BOOST_CHECK_EQUAL(cShape.getFrameRect().height, height);
  BOOST_CHECK_EQUAL(cShape.getNumberOfShapes(), 1);
  BOOST_CHECK_EQUAL(cShape.getArea(), square);
}

BOOST_AUTO_TEST_CASE(composite_shape_move_to_point)
{
  const smirnov::Rectangle rectangle({10,10,CENTER});
  const smirnov::point_t movePoint({1,1});
  smirnov::CompositeShape cShape(std::make_shared<smirnov::Rectangle>(rectangle));
  const double width = cShape.getFrameRect().width;
  const double height = cShape.getFrameRect().height;
  cShape.move(movePoint);

  BOOST_CHECK_CLOSE(cShape.getCenter().x, movePoint.x, DELTA);
  BOOST_CHECK_CLOSE(cShape.getCenter().y, movePoint.y, DELTA);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().pos.x, movePoint.x, DELTA);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().pos.y, movePoint.y, DELTA);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().width, width, DELTA);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().height, height, DELTA);
  BOOST_CHECK_CLOSE(cShape.getArea(), cShape.getArea(), DELTA);
}

BOOST_AUTO_TEST_CASE(composite_shape_move_by_coordinates)
{
  smirnov::Circle circle({10,CENTER});
  const double x = 2, y = 2;
  smirnov::CompositeShape cShape(std::make_shared<smirnov::Circle>(circle));

  const double dx = cShape.getCenter().x;
  const double dy = cShape.getCenter().y;
  const double pos_x = cShape.getFrameRect().pos.x;
  const double pos_y = cShape.getFrameRect().pos.y;
  const double dWidth = cShape.getFrameRect().width;
  const double dHeight = cShape.getFrameRect().height;

  cShape.move(x, y);

  BOOST_CHECK_CLOSE(cShape.getCenter().x, dx + x, DELTA);
  BOOST_CHECK_CLOSE(cShape.getCenter().y, dy + y, DELTA);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().pos.x, pos_x + x, DELTA);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().pos.y, pos_y + y, DELTA);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().width, dWidth, DELTA);
  BOOST_CHECK_CLOSE(cShape.getFrameRect().height, dHeight, DELTA);
  BOOST_CHECK_CLOSE(cShape.getArea(), cShape.getArea(), DELTA);
}

BOOST_AUTO_TEST_CASE(composite_shape_scale_parameters_correctness)
{
  smirnov::CompositeShape rShape;
  rShape.pushBack(std::make_shared<smirnov::Rectangle>
  (smirnov::rectangle_t{2.0, 2.0, CENTER}));

  rShape.pushBack(std::make_shared<smirnov::Rectangle>
  (smirnov::rectangle_t{3.0, 3.0, CENTER}));

  const smirnov::rectangle_t frameRect = rShape.getFrameRect();
  const double area = rShape.getArea();

  const double coef = 2;
  rShape.scale(coef);

  const smirnov::rectangle_t scaledFrameRect = rShape.getFrameRect();
  BOOST_CHECK_CLOSE(rShape.getArea(), area * coef * coef, DELTA);
  BOOST_CHECK_CLOSE(scaledFrameRect.width, frameRect.width * coef, DELTA);
  BOOST_CHECK_CLOSE(scaledFrameRect.height, frameRect.height * coef, DELTA);
  BOOST_CHECK_CLOSE(scaledFrameRect.pos.x, frameRect.pos.x, DELTA);
  BOOST_CHECK_CLOSE(scaledFrameRect.pos.y, frameRect.pos.y, DELTA);
}

BOOST_AUTO_TEST_CASE(composite_shape_scale_parameters_incorrectness)
{
  smirnov::CompositeShape cShape(std::make_shared<smirnov::Circle>(smirnov::Circle(2,CENTER)));
  BOOST_CHECK_THROW(cShape.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(cShape.scale(-3.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(composite_shape_full_area)
{
  const smirnov::Circle c1(2,CENTER);
  const smirnov::Circle c2(3,CENTER);
  const double area = c2.getArea() + c1.getArea();
  smirnov::CompositeShape cShape(std::make_shared<smirnov::Circle>(c1));
  cShape.pushBack(std::make_shared<smirnov::Circle>(c2));
  BOOST_CHECK_CLOSE(cShape.getArea(), area, DELTA);
}

BOOST_AUTO_TEST_CASE(composite_shape_out_of_range)
{
  smirnov::CompositeShape composition;
  for (double i = 1; i < 5; i++)
  {
    composition.pushBack(std::make_shared<smirnov::Rectangle>
  (smirnov::rectangle_t{(0+i),(0+i), CENTER}));
  }
  BOOST_CHECK_THROW(composition[7], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(composite_shape_constructor_correct_framerect)
{
  const double height= 5;
  const double width = 5;
  const smirnov::point_t c{0.5, -3.5};
  smirnov::Rectangle rectangle1({2, 2, {2,-2} });
  smirnov::Rectangle rectangle2({ 4, 2, {0,-5} });
  smirnov::CompositeShape composition(std::make_shared<smirnov::Rectangle>(rectangle1));
  composition.pushBack(std::make_shared<smirnov::Rectangle>(rectangle2));
  BOOST_CHECK_CLOSE(composition.getFrameRect().width, width, DELTA);
  BOOST_CHECK_CLOSE(composition.getFrameRect().height, height, DELTA);
  BOOST_CHECK_CLOSE(composition.getCenter().x,c.x, DELTA);
  BOOST_CHECK_CLOSE(composition.getCenter().y,c.y, DELTA);
}

BOOST_AUTO_TEST_CASE(composite_shape_constructor_copy_and_pop)
{
  smirnov::CompositeShape comp1;
  smirnov::Rectangle rectangle1({2, 2, {2,-2} });
  smirnov::Rectangle rectangle2({ 4, 2, {0,-5} });
  comp1.pushBack(std::make_shared<smirnov::Rectangle>(rectangle1));
  comp1.pushBack(std::make_shared<smirnov::Rectangle>(rectangle2));
  smirnov::CompositeShape comp2(comp1);
  comp2.popBack();

  BOOST_CHECK(comp1.getNumberOfShapes() == (comp2.getNumberOfShapes()+1));
}
