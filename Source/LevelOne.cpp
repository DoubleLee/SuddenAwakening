#include "LevelOne.hpp"

#include "Game.hpp"
#include "StringUtilities.hpp"
#include "XMLFunctions.hpp"
#include "Entity.hpp"
#include "TileMap.hpp"

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
	sf::RenderWindow * pWindow( mpGame->GetWindow() );

	if ( mpTileMap )
		mpTileMap->Draw(pWindow);
	}

void LevelOne::LoadFromXML(const string & file)
	{
	XMLDocument doc;
	if ( doc.LoadFile( file.c_str() ) )
		{
		ThrowRuntimeException("Failed to load xml file, " + file )
		}

	LoadMusicFromXML( *(mpGame->GetMusic()), doc.FirstChildElement("music") );

	string mapFile;
	XMLElement * pMap( doc.FirstChildElement("map") );

	const char * pMapFile = pMap->Attribute("file");
	if ( !pMapFile )
		{
		ThrowRuntimeException("Failed to find map element in Level xml")
		}

	mapFile = pMapFile;

	ToPlatformPath(mapFile);

	mpTileMap.reset( new TileMap( mapFile ) );
	}

void LevelOne::ProcessEvent(const sf::Event & event)
	{

	}
