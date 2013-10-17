#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

#include <string>

#define ThrowRuntimeException( errorDesc ) { throw RuntimeException( __FILE__, __LINE__, errorDesc ); }
#define ThrowRuntimeExceptionStrCode( errorDesc, errorString, errorCode ) { throw RuntimeException( __FILE__, __LINE__, errorDesc, errorString, errorCode); }

class RuntimeException : public std::exception
{
public:
	RuntimeException(const std::string file, const int line, const std::string errorDesc);
	RuntimeException(const std::string file, const int line, const std::string errorDesc, const std::string errorString, int errorCode);

	virtual const char * what() const noexcept;

protected:
	std::string mWhat;
};

#endif // EXCEPTIONS_HPP
