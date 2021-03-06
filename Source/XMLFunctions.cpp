#include "XMLFunctions.hpp"

#include "AudioEffects.hpp"
#include "ResourceManager.hpp"
#include "StringUtilities.hpp"
#include "Entity.hpp"
#include "Level.hpp"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include "tinyxml2.hpp"
using namespace tinyxml2;

#include <stdexcept>
#include <string>
using std::string;

template < class T >
bool IsValidEnum( T & enumRef, int valueID )
	{
	if ( valueID > static_cast<int>(T::BeginID) && valueID < static_cast<int>(T::EndID) )
		{
		enumRef = static_cast<T> (valueID);
		return true;
		}
	return false;
	}

void LoadTexturesFromXML(ResourceManager<sf::Texture> & textures, tinyxml2::XMLElement * pTexturesElement)
	{
	// Make sure element passed in is valid, and the correct one.
	if ( !pTexturesElement || strcmp(pTexturesElement->Name(), "textures") )
		{
		ThrowRuntimeException("LoadTexturesFromXML invalid node passed in")
		}

	// delete any textures old textures if there are any.
	textures.ClearAll();

	// Get first texture element
	XMLElement * pTexIndex( pTexturesElement->FirstChildElement("texture") );

	// loop over each texture element and load them.
	string file;
	ResourceID id;
	while ( pTexturesElement && pTexIndex )
		{

		// Get texture file name and check for validity
		const char * pStr ( pTexIndex->Attribute("file") );
		if ( !pStr )
			{
			ThrowRuntimeException("Failed to load texture file string.")
			}

		file = pStr;

		if ( pTexIndex->QueryUnsignedAttribute("texID", &id) )
			{
			ThrowRuntimeException("Failed to load texture id from xml")
			}

		textures.LoadResource(file, id);

		// Iterate to next texture element.
		pTexIndex = pTexIndex->NextSiblingElement("texture");
		}

	}


void LoadMusicFromXML(sf::Music & music, tinyxml2::XMLElement * pMusicElement)
	{
	// Make sure element passed in is valid, and the correct one.
	if ( !pMusicElement || strcmp(pMusicElement->Name(), "music") )
		{
		ThrowRuntimeException("Load music from xml, invalid node passed in.")
		}

	music.stop();

	// Get music file name attribute from element and check for error
	const char * pStr ( pMusicElement->Attribute("file") );
	if ( !pStr )
		ThrowRuntimeException("No file attribute in music element, use empty string for no music")

	string file(pStr);

	if ( file.empty() )
		{
		ThrowRuntimeException("Music file name is empty.")
		}

	// Tell sf::Music to load file and check for problems
	if ( !music.openFromFile(  ToPlatformPath( file ).c_str() ) )
		{
		ThrowRuntimeException("Failed to load music file into sf::Music")
		}

	float volume ( 100.0f );

	// Get volume from music attribute and check for problems
	if ( pMusicElement->QueryFloatAttribute("volume", & volume) )
		{
		ThrowRuntimeException("Failed to find volume in music element")
		}

	// setup sf::Music settings and play music
	music.setRelativeToListener(true);
	music.setVolume(volume);
	music.setLoop(true);
	music.play();
	}


void LoadAudiosFromXML(AudioEffects & audioMan, tinyxml2::XMLElement * pAudiosElement)
	{
	// Make sure element passed in is valid, and the correct one.
	if ( !pAudiosElement || strcmp( pAudiosElement->Name(), "audios" ) )
		{
		ThrowRuntimeException("Invalid element sent to LoadAudioFromXML")
		}

	audioMan.ClearAll();

	// Get first audio element
	XMLElement * pAudioIndex ( pAudiosElement->FirstChildElement("audio") );

	// Iterate over each audio element
	while ( pAudiosElement && pAudioIndex )
		{
		// Get file name for this audio and check for problems
		const char * pStr ( pAudioIndex->Attribute("file") );
		if ( !pStr )
			ThrowRuntimeException("audio element has no file attribute")

		string file(pStr);

		int audioID = -1;

		// Get audioID from audio element and check for problems
		if ( pAudioIndex->QueryIntAttribute("audioID", &audioID) )
			{
			ThrowRuntimeException("audio element has no audio id attribute")
			}

		AudioID id;

		// Template function to make sure the id is valid
		if ( !IsValidEnum(id, audioID) )
			{
			ThrowRuntimeException("AudioID from audio element is not valid.")
			}

//		AudioID id( static_cast< AudioID > (audioID) );
//		if ( !(audioID < static_cast<int>( decltype(id)::LastID) && audioID > static_cast<int>(decltype(id)::FirstID) ) )
//			{
//			ThrowRuntimeException("AudioID is not a valid id");
//			}

		// Load the audio into the AudioEffects manager in the id group
		if ( !audioMan.LoadBuffer( ToPlatformPath(file), id ) )
			{
			ThrowRuntimeException("Failed while loading audio buffer file")
			}

		// Iterate to next audio element
		pAudioIndex = pAudioIndex->NextSiblingElement("audio");
		}
	}

//void LoadMapTilesFromXML( Level * pLevel, XMLElement * pMapElement)
//	{
//	// map sure we have the correct element
//	if ( !pMapElement || strcmp( pMapElement->Name(), "map" ) )
//		ThrowRuntimeException("Invalid element sent to LoadMapTilesFromXML")

//	// clear the map in case there was already something in it.
//	pLevel->mMapTiles.clear();

//	// get the basic data from map element
//	int mapTileCountHeight, mapTileCountWidth;
//	int tileSizeWidth, tileSizeHeight;

//	if ( pMapElement->QueryIntAttribute("width", &mapTileCountWidth) )
//		ThrowRuntimeException("Map element has no attribute width")

//	if ( pMapElement->QueryIntAttribute("height", &mapTileCountHeight) )
//		ThrowRuntimeException("Map element has no attribute height")

//	if ( pMapElement->QueryIntAttribute("tilewidth", &tileSizeWidth) )
//		ThrowRuntimeException("Map element has no attribute tilewidth")

//	if ( pMapElement->QueryIntAttribute("tileheight", &tileSizeHeight) )
//		ThrowRuntimeException("Map element has no attribute tileheight")

//	XMLElement * pTileSet( pMapElement->FirstChildElement("tileset") );

//	if ( !pTileSet )
//		ThrowRuntimeException("Failed to find tileset element")

//	int layerTileSizeHeight, layerTileSizeWidth;

//	int firstGUID;

//	if ( pTileSet->QueryIntAttribute("tilewidth", &layerTileSizeWidth) )
//		ThrowRuntimeException("Failed to find layers attribute tilewidth")

//	if ( pTileSet->QueryIntAttribute("tileheight", &layerTileSizeHeight) )
//		ThrowRuntimeException("Failed to find layers attribute tileheight")

//	if ( pTileSet->QueryIntAttribute("firstgid", &firstGUID) )
//		ThrowRuntimeException("Failed to find layers attribute firstgid")

//	XMLElement * pImageSet( pTileSet->FirstChildElement("image") );

//	if ( !pImageSet )
//		ThrowRuntimeException("Failed to find image element")

//	unsigned int imageSizeWidth, imageSizeHeight;
//	unsigned int imageSetCountTilesWidth, imageSetCountTilesHeight;
//	const char * pImageName = pImageSet->Attribute("source");

//	if ( !pImageName )
//		ThrowRuntimeException("Failed to find image's attribute source (image file name)")

//	if ( pImageSet->QueryUnsignedAttribute("width", &imageSizeWidth) )
//		ThrowRuntimeException("Failed to find image width attribute")

//	if ( pImageSet->QueryUnsignedAttribute("height", &imageSizeHeight) )
//		ThrowRuntimeException("Failed to find image height attribute")

//	imageSetCountTilesWidth = imageSizeWidth / layerTileSizeWidth;
//	imageSetCountTilesHeight = imageSizeHeight / layerTileSizeHeight;

//	// TODO: make the path names a global function that can be queried.
//	string file( "../Resources/Maps/" );
//	file += pImageName;

//	if ( !pLevel->mpLayerImage->loadFromFile( ToPlatformPath(file) ) )
//		{
//		ThrowRuntimeException("Failed to load map layer image file, " + file)
//		}

//	XMLElement * pLayer( pMapElement->FirstChildElement("layer") );

//	if ( !pLayer )
//		ThrowRuntimeException("Failed to find layer element in map")

//	XMLElement * pData( pLayer->FirstChildElement("data") );

//	if ( !pData )
//		ThrowRuntimeException("Failed to load data element from map")

//	XMLElement * pTileIndex( pData->FirstChildElement("tile") );

//	std::unique_ptr<Entity> pEnt(nullptr);
//	unsigned int gid;
//	sf::IntRect rect;
//	rect.width = layerTileSizeWidth;
//	rect.height = layerTileSizeHeight;
//	sf::Vector2f pos;
//	unsigned int count = 0;
//	while ( pTileIndex )
//		{
//		if ( pTileIndex->QueryUnsignedAttribute("gid", &gid) )
//			{
//			ThrowRuntimeException("Failed to find tile's gid attribute")
//			}

//		// TODO: instead of gid - 1 make it gid - firstgid
//		rect.top = (gid - 1) / imageSetCountTilesHeight;
//		if ( gid == 0 )
//			{
//			pTileIndex = pTileIndex->NextSiblingElement("tile");
//			++count;
//			continue;
//			}

//		rect.left = (gid - 1) % imageSetCountTilesWidth;
//		rect.top *= rect.height;
//		rect.left *= rect.width;

//		pos.x = count % mapTileCountWidth  * rect.width;
//		pos.y = count / mapTileCountHeight * rect.height;

//		pEnt.reset( new Entity( *(pLevel->mpLayerImage.get()), rect, pos ) );

//		pLevel->mTiles.emplace_back( std::move(pEnt) );

//		pTileIndex = pTileIndex->NextSiblingElement("tile");
//		++count;
//		}
//	}
