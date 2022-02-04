#ifndef PHONE_NOTE_HPP
#define PHONE_NOTE_HPP

#include <iostream>
#include <string>
namespace telephonebook
{
  class PhoneNote
  {
  public:
    PhoneNote(std::string number, std::string name);
    std::string phoneNumber_;
    std::string firstName_;
    friend std::ostream& operator<< (std::ostream &out, const PhoneNote &note);
  };
  std::ostream& operator<< (std::ostream &out, const PhoneNote &note);
}

#endif
