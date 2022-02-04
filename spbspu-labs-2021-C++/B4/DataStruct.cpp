#include <iostream>
#include <sstream>
#include "DataStruct.hpp"

bool B4::isKeyValid(const int key)
{
  return((key >= -5) && (key <= 5));
}

bool B4::isStrValid(const std::string& str)
{
  return(!str.empty());
}

int B4::readKey(std::istream& in)
{
  int key = INT32_MAX;
  in >> key;

  if (!isKeyValid(key))
  {
    in.setstate(std::istream::failbit);
  }
  if (in.eof() || in.get() != ',' || in.peek() == '\n')
  {
    in.setstate(std::istream::failbit);
  }
  return key;
}

std::string B4::readStr(std::istream& in)
{
  std::string str;
  std::getline(in, str);
  if (!isStrValid(str))
  {
    in.setstate(std::istream::failbit);
  }
  return str;
}

std::istream& B4::operator>>(std::istream& in, DataStruct& data)
{
  std::string string;
  std::string str;
  int key1, key2;
  std::istream::sentry sentry(in);

  if (sentry)
  {
    key1 = readKey(in);
    key2 = readKey(in);
    str = readStr(in);
  }
  if (in)
  {
    data.key1 = key1;
    data.key2 = key2;
    data.str = str;
  }
  return in;
}

std::ostream& B4::operator<<(std::ostream& out, const DataStruct& data)
{
  out << data.key1 << ',' << data.key2 << ',' << data.str << '\n';
  return out;
}

bool B4::operator<(const DataStruct& first, const DataStruct& second)
{
  if(first.key1 == second.key1)
  {
    if(first.key2 == second.key2)
    {
      return first.str.size() < second.str.size();
    }
    return first.key2 < second.key2;
  }
  return first.key1 < second.key1;
}
