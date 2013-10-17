#include "StringUtilities.hpp"

string & ToPlatformPath(string & str)
	{
	char lookFor;
	char replaceWith;
	#ifdef WIN32
		lookFor = '/';
		replaceWith = '\\';
	#else
		lookFor = '\\';
		replaceWith = '/';
	#endif

	if ( str.empty() )
		return str;

	for ( decltype( str.size() ) i = 0; i < str.size(); ++i )
		{
		if ( str[i] == lookFor )
			str[i] = replaceWith;
		}

	return str;
	}

void StripPath( std::string & fileName )
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
		return;
		}
	else
		{
		++indexLastSlash; // move past '\'
		if ( indexLastSlash < fileName.size() )
			{
			fileName = fileName.substr(indexLastSlash);
			}
		else
			{
			fileName = fileName.substr(--indexLastSlash);
			}
		}

	}
