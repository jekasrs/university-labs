#ifndef WRONG_SIZE_H
#define WRONG_SIZE_H

#include <exception>
#include <string>

class WrongQueueSize : public std::exception
{
public:
	WrongQueueSize() : reason_("WrongQueueSize") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};
#endif
