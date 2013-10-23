#include "ConfigLoader.hpp"

#include "Logger.hpp"
#include "StringUtilities.hpp"
#include "Exceptions.hpp"

#include "tinyxml2.hpp"
using namespace tinyxml2;

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
	LoadFromFile(file);
	}

void ConfigLoader::LoadFromFile(const string &file)
	{
	XMLDocument doc;
	XMLError error = doc.LoadFile( file.c_str() );
	switch(error)
		{
		case(tinyxml2::XML_NO_ERROR):
			{
			LogSuccess("XML-File loaded successfully, " + file)
			break;
			}
		case(tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED):
			{
			ThrowRuntimeException("could not open file " + file)
			}
		case(tinyxml2::XML_ERROR_FILE_NOT_FOUND):
			{
			ThrowRuntimeException("file not found " + file)
			}
		default:
			{
			ThrowRuntimeException("unknown error while loading ConfigLoader's xml file. " + file)
			}
		} // End of Switch

	XMLElement * pGameSettings = doc.FirstChildElement("settings");

	if ( !pGameSettings )
		ThrowRuntimeException("Failed to find settings node")

	if ( pGameSettings->QueryIntAttribute("screenWidth", &mScreenWidth) )
		{
		ThrowRuntimeException("Failed to find screenWidth attribute")
		}

	if ( pGameSettings->QueryIntAttribute("screenHeight", &mScreenHeight) )
		{
		ThrowRuntimeException("Failed to find screenHeight attribute")
		}

	const char * pStr = pGameSettings->Attribute("windowTitle");

	if ( !pStr )
		{
		ThrowRuntimeException("Failed to find windowTitle attribute")
		}

	mWindowTitle = pStr;

	pStr = pGameSettings->Attribute("fontButton");

	if ( !pStr )
		ThrowRuntimeException("Failed to find fontButton attribute")

	mFontButtonFile = pStr;

	ToPlatformPath(mFontButtonFile);
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
