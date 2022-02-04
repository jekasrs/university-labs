#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"

const double DELTA = 0.001;
const smirnov::point_t CENTER = { -2.0, 2.0 };
const double HEIGHT = 2.52;
const double WIDTH = 10.0;

BOOST_AUTO_TEST_CASE(rectanle_constructor_correct_parameters)
{
  smirnov::Rectangle rectangle({WIDTH, HEIGHT, CENTER});

  BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, WIDTH);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, HEIGHT);
  BOOST_CHECK_EQUAL(rectangle.getCenter().x, CENTER.x);
  BOOST_CHECK_EQUAL(rectangle.getCenter().y, CENTER.y);
}

BOOST_AUTO_TEST_CASE(rectanle_constructor_incorrect_height)
{
  BOOST_CHECK_THROW(smirnov::Rectangle({WIDTH, 0.0, CENTER}),
  std::invalid_argument);
  BOOST_CHECK_THROW(smirnov::Rectangle({WIDTH, -3.3, CENTER}),
  std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectanle_constructor_incorrect_width)
{
  BOOST_CHECK_THROW(smirnov::Rectangle({0.0, HEIGHT, CENTER}),
  std::invalid_argument);
  BOOST_CHECK_THROW(smirnov::Rectangle({-3.3, HEIGHT, CENTER}),
  std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_move_point_to_centre)
{
  smirnov::Rectangle rectangle({WIDTH, HEIGHT, CENTER});
  const smirnov::point_t point{ 1.0, 1.0 };
  rectangle.move(point);
  BOOST_CHECK_EQUAL(rectangle.getCenter().x, point.x);
  BOOST_CHECK_EQUAL(rectangle.getCenter().y, point.y);
}

BOOST_AUTO_TEST_CASE(rectangle_move_coordinate_to_centre)
{
  smirnov::Rectangle rectangle({WIDTH, HEIGHT, CENTER});
  const double dx = 1.1111;
  const double dy = 1.0;
  rectangle.move(dx, dy);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, CENTER.x + dx, DELTA);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, CENTER.y + dy, DELTA);
}

BOOST_AUTO_TEST_CASE(rectangle_scaling_incorrect_value)
{
  smirnov::Rectangle rectangle({WIDTH, HEIGHT, CENTER});
  BOOST_CHECK_THROW(rectangle.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_scaling_frameRect_correctness)
{
  smirnov::Rectangle rectangle({WIDTH, HEIGHT, CENTER});
  const double coef = 3.0;
  rectangle.scale(coef);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH * coef, DELTA);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT * coef, DELTA);
  BOOST_CHECK_EQUAL(rectangle.getCenter().x, CENTER.x);
  BOOST_CHECK_EQUAL(rectangle.getCenter().y, CENTER.y);

}

BOOST_AUTO_TEST_CASE(rectangle_area_correctness)
{
  smirnov::Rectangle rectangle({WIDTH, HEIGHT, CENTER});
  BOOST_CHECK_CLOSE(rectangle.getArea(), WIDTH * HEIGHT, DELTA);
}

BOOST_AUTO_TEST_CASE(rectangle_scaling_area_correctness)
{
  smirnov::Rectangle rectangle({WIDTH, HEIGHT, CENTER});
  const double coef = 5.0;
  rectangle.scale(coef);
  const double area = WIDTH * HEIGHT * coef * coef;
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, DELTA);
}

BOOST_AUTO_TEST_CASE(rectangle_scaling_area_incorrectness)
{
  smirnov::Rectangle rectangle({WIDTH, HEIGHT, CENTER});
  const double coef = -5.0;
  BOOST_CHECK_THROW(rectangle.scale(coef), std::invalid_argument);
}
