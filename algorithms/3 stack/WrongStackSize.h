#ifndef STACK_WRONG_STACKSIZE_HPP
#define STACK_WRONG_STACKSIZE_HPP

#include<exception>
#include <string>

class WrongStackSize : public std::exception
{
public:
	WrongStackSize() : reason_("WrongStackSize") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};
#endif
