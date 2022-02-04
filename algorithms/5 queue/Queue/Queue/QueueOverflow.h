#ifndef OVERFLOW_H
#define OVERFLOW_H

#include <exception>
#include <string>

class QueueOverflow : public std::exception
{
public:
	QueueOverflow() : reason_("QueueOverflow") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};
#endif