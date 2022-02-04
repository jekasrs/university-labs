#define BOOST_TEST_DYN_LINK
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE ProjTests
#include <boost/test/included/unit_test.hpp>

#include "shape.hpp"

BOOST_AUTO_TEST_CASE(CORRECT_STR)
{
  smirnov::Point p1s{0,0};
  smirnov::Point p2s{4,0};
  smirnov::Point p3s{4,4};
  smirnov::Point p4s{0,4};
  smirnov::Shape square{p1s,p2s,p3s,p4s};

  smirnov::Point p1r{0,0};
  smirnov::Point p2r{5,0};
  smirnov::Point p3r{5,4};
  smirnov::Point p4r{0,4};
  smirnov::Shape rectangle{p1r,p2r,p3r,p4r};

  BOOST_CHECK(smirnov::isRectangle(square)==true);
  BOOST_CHECK(smirnov::isSquare(square)==true);
  BOOST_CHECK(smirnov::isRectangle(rectangle)==true);
  BOOST_CHECK(smirnov::isSquare(rectangle)==false);
}
