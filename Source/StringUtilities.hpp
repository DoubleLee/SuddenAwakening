#pragma once

#ifndef STRINGUTILITIES_H
#define STRINGUTILITIES_H

#include <string>
using std::string;

string & ToPlatformPath( string & str );
void StripPath( std::string & fileName );

#endif // STRINGUTILITIES_H
