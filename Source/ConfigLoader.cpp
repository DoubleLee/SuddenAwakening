#include "ConfigLoader.h"

#include "Logger.h"
#include "StringUtilities.h"

#include "tinyxml2.h"
using namespace tinyxml2;

#include <exception>
#include <stdexcept>

ConfigLoader::ConfigLoader()
	:
	mScreenWidth(800),
	mScreenHeight(600),
	mWindowTitle("SFML Game!")
	{

	}

ConfigLoader::ConfigLoader(const string & file)
	:
	ConfigLoader()
	{
	if ( !LoadFromFile(file) )
		throw std::invalid_argument("Can't parse xml file.");
	}

bool ConfigLoader::LoadFromFile(const string &file)
	{
	XMLDocument doc;
	XMLError error = doc.LoadFile( file.c_str() );
	switch(error)
		{
		case(tinyxml2::XML_NO_ERROR):
			{
			LogSuccess("XML-File loaded successful\n")
			break;
			}
		case(tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED):
			{
			LogFailure("could not open file\n")
			return false;
			}
		case(tinyxml2::XML_ERROR_FILE_NOT_FOUND):
			{
			LogFailure("file not found\n")
			return false;
			}
		default:
			{
			LogFailure("unknown error\n")
			return false;
			}
		} // End of Switch

	XMLElement * pGameSettings = doc.FirstChildElement("settings");

	if ( !pGameSettings )
		return false;

	if ( pGameSettings->QueryIntAttribute("screenWidth", &mScreenWidth) )
		{
		return false;
		}

	if ( pGameSettings->QueryIntAttribute("screenHeight", &mScreenHeight) )
		{
		return false;
		}

	const char * pStr = pGameSettings->Attribute("windowTitle");

	if ( !pStr )
		{
		return false;
		}

	mWindowTitle = pStr;

	pStr = pGameSettings->Attribute("fontButton");

	if ( !pStr )
		return false;

	mFontButtonFile = pStr;

	ToPlatformPath(mFontButtonFile);

	return true;
	}

int ConfigLoader::GetScreenWidth() const
	{
	return mScreenWidth;
	}

int ConfigLoader::GetScreenHeight() const
	{
	return mScreenHeight;
	}

const std::string & ConfigLoader::GetWindowTitle() const
	{
	return mWindowTitle;
	}

const std::string & ConfigLoader::GetFontButtonFile() const
	{
	return mFontButtonFile;
	}
