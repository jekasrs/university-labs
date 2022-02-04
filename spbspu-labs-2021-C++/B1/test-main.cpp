#define BOOST_TEST_DYN_LINK
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE ProjTests
#include <boost/test/included/unit_test.hpp>

#include "tasks.hpp"
#include "utilities.hpp"

#include <forward_list>

BOOST_AUTO_TEST_CASE(CORRECT_ORDER_ASCENDING)
{
  std::vector<int> dirtyVecor;
  dirtyVecor.push_back(9);
  dirtyVecor.push_back(3);
  dirtyVecor.push_back(2);
  dirtyVecor.push_back(6);
  dirtyVecor.push_back(1);
  dirtyVecor.push_back(0);
  dirtyVecor.push_back(4);
  dirtyVecor.push_back(5);
  dirtyVecor.push_back(8);
  dirtyVecor.push_back(7);
  std::vector<int> vectorAccendinCorrect;

  for(int i = 0; i<10;i++)
  {
    vectorAccendinCorrect.push_back(i);
  }

  utilities::bubbleSort<IteratorConteiner>(dirtyVecor,utilities::directionType<int>("ascending"));
  BOOST_CHECK(dirtyVecor == vectorAccendinCorrect);
}

BOOST_AUTO_TEST_CASE(CORRECT_ORDER_DESCENDING)
{
  std::vector<int> dirtyVecor;
  dirtyVecor.push_back(9);
  dirtyVecor.push_back(3);
  dirtyVecor.push_back(2);
  dirtyVecor.push_back(6);
  dirtyVecor.push_back(1);
  dirtyVecor.push_back(0);
  dirtyVecor.push_back(4);
  dirtyVecor.push_back(5);
  dirtyVecor.push_back(8);
  dirtyVecor.push_back(7);
  std::vector<int> vectorDescendingCorrect;
  for(int i = 0; i<10;i++)
  {
    vectorDescendingCorrect.push_back(9-i);
  }
  utilities::bubbleSort<IteratorConteiner>(dirtyVecor,utilities::directionType<int>("descending"));
  BOOST_CHECK(dirtyVecor == vectorDescendingCorrect);
}

BOOST_AUTO_TEST_CASE(NULL_VALUES_AND_ERRORS)
{
  BOOST_CHECK_THROW(utilities::directionType<int>(nullptr),std::invalid_argument);
  BOOST_CHECK_THROW(utilities::directionType<int>("pressF"),std::invalid_argument);
  BOOST_CHECK_NO_THROW(utilities::directionType<int>("ascending"));
}

BOOST_AUTO_TEST_CASE(NULL_VALUES_AND_ERRORS_DIFFREREN_CONTAINERS)
{
  std::vector<int> v1;
  std::forward_list<int> l1;

  BOOST_CHECK_NO_THROW(utilities::bubbleSort<IteratorConteiner>(v1,utilities::directionType<int>("ascending")));
  BOOST_CHECK_NO_THROW(utilities::bubbleSort<IteratorConteiner>(l1,utilities::directionType<int>("ascending")));

}

BOOST_AUTO_TEST_CASE(TASK1_NO_REAL_FILE)
{
 BOOST_CHECK_THROW(secondTask("data.txt"),std::ios_base::failure);
}
