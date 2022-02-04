#define BOOST_TEST_DYN_LINK
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE ProjTests
#include <boost/test/included/unit_test.hpp>

#include "checkIn.hpp"
#include "PhoneBookInterface.hpp"

telephonebook::PhoneBookInterface Contacts(std::make_unique<telephonebook::PhoneBook>(telephonebook::PhoneBook()));

BOOST_AUTO_TEST_CASE(CORRECT_CHECKERS_NUMBER)
{
  std::string str1 = "89522705509";
  std::string str2 = "895227O95509";
  std::string str3 = "";
  BOOST_CHECK(checker::isNumberCorrect(str1)==true);
  BOOST_CHECK(checker::isNumberCorrect(str2)==false);
  BOOST_CHECK(checker::isNumberCorrect(str3)==false);
}

BOOST_AUTO_TEST_CASE(CORRECT_CHECKERS_NAME)
{
  std::string str1 = "\"Evgeny\"";
  std::string str2 = "\"Evgeny\"st\"\"";
  std::string str3 = "Evgeny";
  std::string str4 = "";

  BOOST_CHECK(checker::isNameCorrect(str1)==true);
  BOOST_CHECK(checker::isNameCorrect(str2)==true);
  BOOST_CHECK(checker::isNameCorrect(str3)==false);
  BOOST_CHECK(checker::isNameCorrect(str4)==false);

  checker::deleteRubish(str1);
  checker::deleteRubish(str2);
  BOOST_CHECK(str1=="Evgeny");
  BOOST_CHECK(str2=="Evgeny\"st\"");
}

BOOST_AUTO_TEST_CASE(CORRECT_CHECKERS_MARK_NAME)
{
  std::string str1 = "\"MarkNAME\"";
  std::string str2 = "MarkNAME";
  std::string str3 = "Mark-NAME";
  std::string str4 = "Mark0NAME";
  std::string str5 = "Mark(NAME";
  std::string str6 = "";

  BOOST_CHECK(checker::isMarkNameCorrect(str1)==false);
  BOOST_CHECK(checker::isMarkNameCorrect(str2)==true);
  BOOST_CHECK(checker::isMarkNameCorrect(str3)==true);
  BOOST_CHECK(checker::isMarkNameCorrect(str4)==true);
  BOOST_CHECK(checker::isMarkNameCorrect(str5)==false);
  BOOST_CHECK(checker::isMarkNameCorrect(str6)==false);
}
