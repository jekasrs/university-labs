#define BOOST_TEST_DYN_LINK
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE ProjTests
#include <boost/test/included/unit_test.hpp>

#include "DataStruct.hpp"

BOOST_AUTO_TEST_CASE(CORRECT_STR)
{
  std::string notInit;
  std::string empty = "";
  std::string correct = "qwerty";
  BOOST_CHECK(B4::isStrValid(notInit)==false);
  BOOST_CHECK(B4::isStrValid(empty)==false);
  BOOST_CHECK(B4::isStrValid(correct)==true);
}

BOOST_AUTO_TEST_CASE(CORRECT_KEY)
{
  int key1 = -5;
  int key2 = 5;
  int key3 = 6;
  int key4 = 0.0;
  BOOST_CHECK(B4::isKeyValid(key1)==true);
  BOOST_CHECK(B4::isKeyValid(key2)==true);
  BOOST_CHECK(B4::isKeyValid(key3)==false);
  BOOST_CHECK(B4::isKeyValid(key4)==true);
}
