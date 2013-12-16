#pragma once

#ifndef STRINGUTILITIES_H
#define STRINGUTILITIES_H

#include <string>
using std::string;

/**
 * @brief ToPlatformPath ensures the file name and paths are in the correct format, supports / and \ slashes.
 * @param str The file name and path to change.
 * @return The file name and path, which is now platform correct.
 */
string & ToPlatformPath( string & str );

/**
 * @brief StripPath removes the path information ( folders ), and leaves the file name and extension ( if any ).
 * @param fileName The file to strip the path from.
 */
void StripPath( std::string & fileName );

#endif // STRINGUTILITIES_H
