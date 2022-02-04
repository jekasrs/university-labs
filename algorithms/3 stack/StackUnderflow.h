#ifndef STACK_UNDERFLOW_HPP
#define STACK_UNDERFLOW_HPP

#include<exception>
#include <string>

class StackUnderFlow : public std::exception
{
public:
	StackUnderFlow() : reason_("StackUnderFlow") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};
#endif
