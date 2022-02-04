#ifndef DATA_STRUCT
#define DATA_STRUCT

#include <string>
#include <iosfwd>
namespace B4
{
  struct DataStruct
  {
    int key1;
    int key2;
    std::string str;
  };

  bool isKeyValid(const int number);
  bool isStrValid(const std::string& str);
  int readKey(std::istream& in);
  std::string readStr(std::istream& in);

  bool operator<(const DataStruct& first, const DataStruct& second);
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif
