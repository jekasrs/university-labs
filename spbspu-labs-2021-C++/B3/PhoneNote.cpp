#include "PhoneNote.hpp"

telephonebook::PhoneNote::PhoneNote(std::string number, std::string name):
  phoneNumber_(number),
  firstName_(name)
{
  if (!(number.size()>0 && name.size()>0))
  {
    std::cerr << "Invalid notes for contact";
  }
}

std::ostream& telephonebook::operator<< (std::ostream &out, const PhoneNote &note)
{
  if (note.phoneNumber_.size()>0 && note.firstName_.size()>0)
  out << note.phoneNumber_ << " " << note.firstName_ << "\n";
  return out;
}
