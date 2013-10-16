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

