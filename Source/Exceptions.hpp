#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

#include <string>

class RuntimeException : public std::exception
{
public:
	RuntimeException(const std::string errorDesc);
	RuntimeException(const std::string errorDesc, const std::string errorString, int errorCode);

	virtual const char * what() const noexcept;

protected:
	std::string mWhat;
};

#endif // EXCEPTIONS_HPP
