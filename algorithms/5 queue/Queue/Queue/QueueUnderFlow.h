#ifndef UNDERFLOW_H
#define UNDERFLOW_H

#include<exception>
#include <string>

class QueueUnderFlow : public std::exception
{
public:
	QueueUnderFlow() : reason_("QueueUnderFlow") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};
#endif