#include <boost/test/unit_test.hpp>
#include "circle.hpp"

const double DELTA = 0.1;
const double RADIUS = 10;
const double CENTRE_X = 1.0;
const double CENTRE_Y = -2.0;
const smirnov::point_t CENTER{CENTRE_X,CENTRE_Y};
const double FRAME_RECT_SIDE = 2 * RADIUS;
const double COEFFICIENT = 1.5;

BOOST_AUTO_TEST_CASE(circle_constructor_correct_arguments_noexception)
{
  smirnov::Circle circle(RADIUS,CENTER);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width/2, RADIUS, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().x, CENTRE_X, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().y, CENTRE_Y, DELTA);
}

BOOST_AUTO_TEST_CASE(circle_constructor_invalidradius_exceptionthrow)
{
  BOOST_CHECK_THROW(smirnov::Circle circle((RADIUS * (-1)),CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(smirnov::Circle circle(0.0,CENTER), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(circle_work_check)
{
  smirnov::Circle circle(RADIUS,CENTER);
  BOOST_CHECK_CLOSE(circle.getArea(),314.15 , DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTRE_X, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTRE_Y, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, FRAME_RECT_SIDE, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, FRAME_RECT_SIDE, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().x, CENTRE_X, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().y, CENTRE_Y, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width/2, RADIUS, DELTA);
}

BOOST_AUTO_TEST_CASE(circle_moving_to_point_valid_arguments_noexeption)
{
  smirnov::Circle circle(RADIUS,CENTER);
  const smirnov::point_t newCentre{ 2.0, -2.0 };
  circle.move(newCentre);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width/2, RADIUS, DELTA);
  BOOST_CHECK_CLOSE(circle.getArea(), 314.15, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().x, newCentre.x, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().y, newCentre.y, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, newCentre.x, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, newCentre.y, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, FRAME_RECT_SIDE, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, FRAME_RECT_SIDE, DELTA);
}

BOOST_AUTO_TEST_CASE(circle_moving_coordinates_valid_arguments_noexception)
{
  smirnov::Circle circle(RADIUS,CENTER);
  const double dx = -0.345, dy = 54.3;
  circle.move(dx, dy);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width/2, RADIUS, DELTA);
  BOOST_CHECK_CLOSE(circle.getArea(),314.15, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().x, CENTRE_X + dx, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().y, CENTRE_Y + dy, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTRE_X + dx, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTRE_Y + dy, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, FRAME_RECT_SIDE, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, FRAME_RECT_SIDE, DELTA);
}

BOOST_AUTO_TEST_CASE(circle_scaling_positive_coefficient_noexceptions)
{
  smirnov::Circle circle(RADIUS,CENTER);
  circle.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width/2, RADIUS * COEFFICIENT, DELTA);
  BOOST_CHECK_CLOSE(circle.getArea(), 314.15 * COEFFICIENT * COEFFICIENT, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().x, CENTRE_X, DELTA);
  BOOST_CHECK_CLOSE(circle.getCenter().y, CENTRE_Y, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTRE_X, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTRE_Y, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, FRAME_RECT_SIDE * COEFFICIENT, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, FRAME_RECT_SIDE * COEFFICIENT, DELTA);
}

BOOST_AUTO_TEST_CASE(circle_scaling_invalid_coefficient_exception)
{
  smirnov::Circle circle(RADIUS,CENTER);
  BOOST_CHECK_THROW(circle.scale(COEFFICIENT * (-1)), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(0.0), std::invalid_argument);
}
