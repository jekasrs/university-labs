#ifndef STACK_OVERFLOW_HPP
#define STACK_OVERFLOW_HPP

#include<exception>
#include <string>

class StackOverflow : public std::exception
{
public:
	StackOverflow() : reason_("StackOverflow") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};
#endif
