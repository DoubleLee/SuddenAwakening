/*
Copyright 2013 @ Chris Leisure
All rights reserved.
*/

#pragma once

//#include <sstream>

#include <string>
#include <iosfwd>

using std::string;
using std::ofstream;

// #if !defined(NDEBUG) which effectively means if not in not debug
// or if we are in debug.

#if !defined(NDEBUG) // debug mode

	// supports visual studio, mingw, and g++
	#define LogFuncBegin() gLogger.FuncBegin( __PRETTY_FUNCTION__ );
	#define LogFuncEndSuccess() gLogger.FuncEndSuccess( __PRETTY_FUNCTION__ );


	// calls appropriate functions for message logging
	#define LogMessage( desc ) gLogger.Message( desc, __FILE__, __LINE__ );
	// calls appropriate function for success logging
	#define LogSuccess( desc ) gLogger.Success( desc, __FILE__, __LINE__ );
	// call appropriate function for warning logging
	#define LogWarning( desc ) gLogger.Warning( desc, __FILE__, __LINE__ );
	// calls appropriate function for error logging
	#define LogError( desc, error, code ) gLogger.Error( __FILE__, __LINE__, desc, error, code );
	#define LogFailure( desc ) gLogger.Failure( __FILE__, __LINE__, desc );

#else // release mode
	#define LogFuncBegin()
	#define LogFuncEndSuccess()

	// resolves to nothing in release mode
	#define LogMessage( desc )
	// resolves to nothing in release mode
	#define LogSuccess( desc )
	// resolves to nothing in release mode
	#define LogWarning( desc ) gLogger.Warning( desc, __FILE__, __LINE__ );
	// Logs failures in release mode
	#define LogError( desc, error, code ) gLogger.Error( __FILE__, __LINE__, desc, error, code );
	#define LogFailure( desc ) gLogger.Failure( __FILE__, __LINE__, desc );
#endif


// this class provides a set of functions for
// logging errors, success and messages
// and writes them to a log file.
// you shouldn't call these functions directly instead use the
// LogMessage, LogSuccess, LogError, LogFailure macros, they do some extra
// work to make things very simple
// the LogMessage and LogSuccess macros resolve to nothing in release mode
// so they will not slow the engine down.
// Only the LogError, LogFailure, and LogWarning macros will resolve, so in release mode errors and warnings are still logged
class Logger
{
public:
	Logger(const std::string& file);
	~Logger();

	// logs the begin of a function, can be useful for automatted logs to visualize the code
	void FuncBegin(const string& function = "Not supported");
	// logs the successful end of a function, can be usefull for automated logs to visualize the code
	void FuncEndSuccess(const string& function = "Not supported");

	// logs a message
	void Message(const string& desc, const string& file, const unsigned long long line);

	// logs a success
	void Success(const string& desc, const string& file, const unsigned long long line);

	// logs a warning
	void Warning(const string& desc, const string& file, const unsigned long long line);

	void Exception( const std::exception & except );

	// logs an error with strings and error code
	void Error(const string& file, const unsigned long long line, const string& desc, const string& error = string(), const int errorCode = 0);

	// logs a failure with string
	void Failure(const string& file, const unsigned long long line, const string& desc);

protected:
	ofstream* mpOfs;

	void LogFileLineDesc(const string& file, const unsigned long long line, const string& desc);
	void PutTimeStr();

private:
	Logger(const Logger& other);	// copy ctor private
	Logger(const Logger && other);		// move ctor private
	Logger& operator = (const Logger& other);	// assignment operator private
	Logger& operator = (const Logger && other);		// move assignment operator private

};

extern Logger gLogger;
