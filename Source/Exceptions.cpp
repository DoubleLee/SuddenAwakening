#include "Exceptions.hpp"

RuntimeException::RuntimeException(const std::string errorDesc)
	:
	std::exception(),
	mWhat(errorDesc)
	{

	}

RuntimeException::RuntimeException(const std::string errorDesc, const std::string errorString, int errorCode = -1)
	:
	std::exception(),
	mWhat()
	{
	mWhat += "ErrorDesc: ";
	mWhat += errorDesc;
	mWhat += "ErrorString: ";
	mWhat += errorString;
	mWhat += "ErrorCode: ";
	mWhat += std::to_string(errorCode);
	}

const char * RuntimeException::what() const noexcept
	{
	return mWhat.c_str();
	}
