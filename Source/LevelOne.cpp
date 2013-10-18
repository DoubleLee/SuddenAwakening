#include "LevelOne.hpp"

#include "Game.hpp"
#include "StringUtilities.hpp"
#include "XMLFunctions.hpp"

#include "tinyxml2.hpp"
using namespace tinyxml2;


LevelOne::LevelOne()
	:
	Level( LevelID::LevelOne )
	{
	string file("../Resources/Scripts/LevelOne.xml");
	LoadFromXML( ToPlatformPath(file) );
	}

LevelOne::~LevelOne()
	{

	}

void LevelOne::Update()
	{

	}

void LevelOne::Draw()
	{

	}

void LevelOne::LoadFromXML(const string & file)
	{
	XMLDocument doc;
	if ( doc.LoadFile( file.c_str() ) )
		{
		ThrowRuntimeException("Failed to load xml file, " + file )
		}

	LoadMusicFromXML( *(mpGame->GetMusic()), doc.FirstChildElement("music") );
	}

void LevelOne::ProcessEvent(const sf::Event & event)
	{

	}
