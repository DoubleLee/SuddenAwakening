/*
Copyright 2013 @ Chris Leisure
All rights reserved.
*/

#include "Logger.hpp"
#include "Exceptions.hpp"

#include <time.h>
#include <stdio.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <cstring>


using namespace std;

Logger gLogger("LogFile.log");

std::string StripPath( const std::string & fileName )
	{
	char lookFor;
#ifdef WIN32
	lookFor = '\\';
#else
	lookFor = '/';
#endif
	string::size_type indexLastSlash = fileName.find_last_of(lookFor);
	if ( indexLastSlash == string::npos )
		{
		return fileName;
		}
	else
		{
		++indexLastSlash; // move past '\'
		if ( indexLastSlash < fileName.size() )
			{
			return fileName.substr(indexLastSlash);
			}
		else
			{
			return fileName.substr(--indexLastSlash);
			}
		}

	}

Logger::Logger(const std::string & file)
	:
	mpOfs( new ofstream() )
	{
	(*mpOfs).open(file, ios::out );
	if ( !mpOfs->is_open() )
		{
		ThrowRuntimeException("Failed to open or create log file.");
		}
	}

Logger::~Logger()
	{
	(*mpOfs).close();
	delete mpOfs;
	}

void Logger::FuncBegin( const string & function )
	{
	PutTimeStr();
	(*mpOfs) << " FUNCTION   " << "BEGIN  " << function << '\n';
	}

void Logger::FuncEndSuccess(const string & function)
	{
	PutTimeStr();
	(*mpOfs) << " FUNCTION   " << "END    " << function << '\n';
	}

void Logger::Message( const string & desc, const string & file, const unsigned long long line )
	{
	PutTimeStr();
	(*mpOfs) << " MESSAGE    ";
	LogFileLineDesc(file,line,desc);
	}

void Logger::Success( const string & desc, const string & file, const unsigned long long line )
	{
	PutTimeStr();
	(*mpOfs) << " SUCCESS    ";
	LogFileLineDesc(file,line,desc);
	}

void Logger::Warning( const string & desc, const string & file, const unsigned long long line )
	{
	PutTimeStr();
	(*mpOfs) << " WARNING    ";
	LogFileLineDesc(file,line,desc);
	}

void Logger::Exception(const exception & except)
	{
	PutTimeStr();
	(*mpOfs) << " EXCEPTION  ";
	(*mpOfs) << except.what();
	}

void Logger::Error( const string & file, const unsigned long long line, const string & desc, const string & error, const int code)
	{
	string strippedFileName(StripPath(file));
	PutTimeStr();
	(*mpOfs) << " ERROR     " << "FILE: " << strippedFileName << " LINE: " << line << " ERROR_CODE: " << code << " DESC: " << desc;

	if ( !error.empty() )
		{
		(*mpOfs) << " ERROR_STR: " << error;
		}
	(*mpOfs) << '\n';
	}

void Logger::Failure( const string & file, const unsigned long long line, const string & desc)
	{
	PutTimeStr();
	(*mpOfs) << " FAILURE     ";
	LogFileLineDesc(file, line, desc);
	}

void Logger::PutTimeStr( )
	{ // changed to use localtime instead of localtime_s ( cross platfrom now )
	time_t rawTime = chrono::system_clock::to_time_t( chrono::system_clock::now() );

	string buffer;
	buffer.resize(30,0);

	strftime(&buffer[0], buffer.size(), "%c", localtime(&rawTime));
	buffer.resize( strlen(&buffer[0]) );
	(*mpOfs) << buffer;
	}

void Logger::LogFileLineDesc( const string & file, const unsigned long long line, const string & desc )
	{
	string strippedFileName(StripPath(file));
	(*mpOfs) << "FILE: " << strippedFileName << " LINE: " << line << " DESC: " << desc << '\n';
	}
