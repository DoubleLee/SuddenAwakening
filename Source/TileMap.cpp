#include "TileMap.hpp"

#include "Game.hpp"
#include "StringUtilities.hpp"
#include "Exceptions.hpp"

#include "tinyxml2.hpp"
using namespace tinyxml2;

#include "SFML/Graphics.hpp"

TileMap::TileMap( const std::string & file )
	:
	mFile(file)
	{
	LoadFromFile();
	}

void TileMap::LoadFromFile()
	{
	LoadFromFile(mFile);
	}

void TileMap::LoadFromFile( const std::string & file )
	{
	// Load Tiled map xml file
	XMLDocument doc;
	if ( doc.LoadFile(file) )
		{
		ThrowRuntimeException("Failed to load xml map file, " + file )
		}

	// Get the map element and load it's attribute data
	XMLElement * pMapElement( doc.FirstChildElement("map") );

	if ( !pMapElement )
		ThrowRuntimeException("Failed to find map element in xml file, " + file)

	if ( pMapElement->QueryFloatAttribute("version", &mFileVersion) )
		{
		ThrowRuntimeException("Failed to find attribute version in xml file, " + file)
		}

	const char * pStr( pMapElement->Attribute("orientation") );

	if ( !pStr )
		{
		ThrowRuntimeException("Failed to find attribute orientation in xml file, " + file)
		}

	mOrientation = pStr;

	if ( pMapElement->QueryUnsignedAttribute("width", &mTileWidthCount) )
		ThrowRuntimeException("Failed to find attribute width in xml file, " + file)

	if ( pMapElement->QueryUnsignedAttribute("height", &mTileHeightCount) )
		ThrowRuntimeException("Failed to find attribute height in xml file, " + file)

	if ( pMapElement->QueryUnsignedAttribute("tilewidth", &mTileWidthSize) )
		ThrowRuntimeException("Failed to find attribute tilewidth in xml file, " + file)

	if ( pMapElement->QueryUnsignedAttribute("tileheight", &mTileHeightSize) )
		ThrowRuntimeException("Failed to find attribute tileheight in xml file, " + file)

	// Get the tileset nodes and load their data
	XMLElement * pTileSetIndex( pMapElement->FirstChildElement("tileset") );

	if ( !pTileSetIndex )
		ThrowRuntimeException("Failed to find element tileset in xml file, " + file)

	unsigned int gid, tileWidthSize, tileHeightSize, imageWidthSize, imageHeightSize;
	unsigned int tilesWidthCount, tilesHeightCount;

	string tileSetName;
	string texFile;

	unique_ptr< TileMapSet > pTileMapSet;

	while( pTileSetIndex )
		{

		if ( pTileSetIndex->QueryUnsignedAttribute("firstgid", &gid) )
			ThrowRuntimeException("Failed to find attribute firstgid in xml file, " + file)

		pStr = pTileSetIndex->Attribute("name");

		if ( !pStr )
			ThrowRuntimeException("Failed to find attribute name in xml file, " + file)

		tileSetName = pStr;
		ToPlatformPath(tileSetName);

		if ( pTileSetIndex->QueryUnsignedAttribute("tilewidth", &tileWidthSize) )
			ThrowRuntimeException("Failed to find attribute tileWidth in xml file, " + file)

		if ( pTileSetIndex->QueryUnsignedAttribute("tileheight", &tileHeightSize) )
			ThrowRuntimeException("Failed to find attribute tileheight in xml file, " + file)

		XMLElement * pImageElement( pTileSetIndex->FirstChildElement("image") );

		if ( !pImageElement )
			ThrowRuntimeException("Failed to find element image in xml file, " + file)

		pStr = pImageElement->Attribute("source");

		if ( !pStr )
			ThrowRuntimeException("Failed to find attribute source in xml file, " + file)

		texFile = pStr;
		ToPlatformPath(texFile);

		if ( pImageElement->QueryUnsignedAttribute("width", &imageWidthSize) )
			ThrowRuntimeException("Failed to find attribute width in xml file, " + file)

		if ( pImageElement->QueryUnsignedAttribute("height", &imageHeightSize) )
			ThrowRuntimeException("Failed to find attribute height in xml file, " + file)

		// Add data loaded for this tile set, construct class and insert into vector

		pTileMapSet.reset( new TileMapSet( texFile, gid, tileSetName, tileWidthSize, tileHeightSize, imageWidthSize, imageHeightSize ) );

		mTileSets.push_back( std::move( pTileMapSet ) );

		// Advance to next tileset element
		pTileSetIndex = pTileSetIndex->NextSiblingElement("tileset");
		}

	// TODO: load the entities and write the GetTilePairFromGid function

	}

void TileMap::Update()
	{

	}

void TileMap::Draw() const
	{
	for ( unique_ptr< TileMapLayer > pTileMapLayer : mTileMapLayers )
		{
		pTileMapLayer->Draw();
		}
	}

TileMapSet::TileMapSet(const std::string &texFile, unsigned int firstGid, const std::string &tileSetName, unsigned int tileWidthSize, unsigned int tileHeightSize, unsigned int imageWidthSize, unsigned int imageHeightSize)
	:
	mFirstGid(firstGid),
	mTileSetName(tileSetName),
	mTileWidthSize(tileWidthSize),
	mTileHeightSize(tileHeightSize),
	mImageWidthSize( imageWidthSize ),
	mImageHeightSize( imageHeightSize ),
	mTilesWidthCount( mImageWidthSize / mTileWidthSize ),
	mTilesHeightCount( mImageHeightSize / mTileHeightSize ),
	mpTexture( new sf::Texture() ),
	mTextureFile(texFile)
	{
	if ( !mpTexture->LoadFromFile( texFile ) )
		ThrowRuntimeException("Failed to load texture for map, " + texFile)

	}

TileMapLayer::TileMapLayer()
	{

	}

TileMapLayer::~TileMapLayer()
	{

	}

void TileMapLayer::Update()
	{

	}

void TileMapLayer::Draw() const
	{
	sf::RenderWindow * pWindow(Game::Get()->GetWindow());

	for ( unique_ptr< Entity > & pEntity : mTileEntities )
		{
		pEntity->Draw(pWindow);
		}
	}
