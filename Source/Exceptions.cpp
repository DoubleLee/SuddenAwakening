#include "Exceptions.hpp"

#include "StringUtilities.hpp"


void BuildLogMessage( std::string & logMessage, const std::string & file, const int line, const std::string & errorDesc )
	{
	std::string fileNoPath(file);
	StripPath(fileNoPath);
	logMessage.reserve( logMessage.size() + fileNoPath.size() + 10 + errorDesc.size() );
	logMessage += "ErrorDesc: ";
	logMessage += errorDesc;
	logMessage += " File: ";
	logMessage += fileNoPath;
	logMessage += " Line: ";
	logMessage += std::to_string(line);
	}

void BuildLogMessageStrCode(std::string & logMessage, const std::string & file, const int line, const std::string & errorDesc, const std::string & errorString, const int errorCode )
	{
	BuildLogMessage(logMessage, file, line, errorDesc);
	logMessage.reserve( logMessage.size() + errorString.size() + 10 );
	logMessage += " ErrorString: ";
	logMessage += errorString;
	logMessage += " ErrorCode: ";
	logMessage += std::to_string(errorCode);
	}

RuntimeException::RuntimeException(const std::string file, const int line, const std::string errorDesc)
	:
	std::exception(),
	mWhat()
	{
	BuildLogMessage(mWhat, file, line, errorDesc);
	}

RuntimeException::RuntimeException(const std::string file, const int line, const std::string errorDesc, const std::string errorString, int errorCode = -1)
	:
	std::exception(),
	mWhat()
	{
	BuildLogMessageStrCode(mWhat, file, line, errorDesc, errorString, errorCode);
	}

const char * RuntimeException::what() const noexcept
	{
	return mWhat.c_str();
	}
