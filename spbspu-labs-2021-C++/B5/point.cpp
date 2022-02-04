#include <iostream>
#include <cmath>
#include <cctype>
#include "point.hpp"

std::istream& smirnov::myskipws(std::istream& in)
{
  while (isblank(in.peek()))
  {
    in.get();
  }
  if (in.peek() == '\n')
  {
    in.setstate(std::istream::failbit);
  }
  return in;
}

char smirnov::readSymbol(std::istream& in)
{
  char s = '\0';
  in >> myskipws;
  s = in.get();
  if (in.peek() == '\n')
  {
    in.setstate(std::istream::failbit);
    return s;
  }
  return s;
}

std::istream& smirnov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sin(in);
  if (!sin)
  {
    in.setstate(std::istream::failbit);
    return in;
  }

  int x = 0;
  int y = 0;
  char openbracket = '\0';
  char semilcon = '\0';
  char closebracket = '\0';

  openbracket = readSymbol(in);
  if (openbracket != '(')
  {
    in.setstate(std::istream::failbit);
    return in;
  }
  in >> myskipws >> x;
  semilcon = readSymbol(in);
  if (semilcon != ';')
  {
    in.setstate(std::istream::failbit);
    return in;
  }
  in >> myskipws >> y;
  in >> myskipws >> closebracket;
  if (closebracket != ')')
  {
    in.setstate(std::istream::failbit);
    return in;
  }

  if (sin)
  {
    point = { x , y };
  }
  return in;
}

std::ostream& smirnov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sot(out);
  if (sot)
  {
    out << '(' << point.x << ';' << point.y << ')';
  }
  return out;
}

double smirnov::findDistance(const Point& p1, const Point& p2)
{
  return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
