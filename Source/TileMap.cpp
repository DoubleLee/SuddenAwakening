#include "TileMap.hpp"

#include "Game.hpp"
#include "Entity.hpp"
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

TileMap::~TileMap()
	{

	}

void TileMap::LoadFromFile( )
	{
	// Load Tiled map document from xml file
	XMLDocument doc;
	if ( doc.LoadFile(mFile.c_str()) )
		{
		ThrowRuntimeException("Failed to load xml map file, " + mFile )
		}

	// Get the map element and load it's attribute data
	XMLElement * pMapElement( doc.FirstChildElement("map") );

	if ( !pMapElement )
		ThrowRuntimeException("Failed to find map element in xml file, " + mFile)

	if ( pMapElement->QueryFloatAttribute("version", &mFileVersion) )
		{
		ThrowRuntimeException("Failed to find attribute version in xml file, " + mFile)
		}

	const char * pStr( pMapElement->Attribute("orientation") );

	if ( !pStr )
		{
		ThrowRuntimeException("Failed to find attribute orientation in xml file, " + mFile)
		}

	mOrientation = pStr;

	if ( pMapElement->QueryUnsignedAttribute("width", &mTileWidthCount) )
		ThrowRuntimeException("Failed to find attribute width in xml file, " + mFile)

	if ( pMapElement->QueryUnsignedAttribute("height", &mTileHeightCount) )
		ThrowRuntimeException("Failed to find attribute height in xml file, " + mFile)

	if ( pMapElement->QueryUnsignedAttribute("tilewidth", &mTileWidthSize) )
		ThrowRuntimeException("Failed to find attribute tilewidth in xml file, " + mFile)

	if ( pMapElement->QueryUnsignedAttribute("tileheight", &mTileHeightSize) )
		ThrowRuntimeException("Failed to find attribute tileheight in xml file, " + mFile)

	// Get the tileset nodes and load their data
	XMLElement * pTileSetIndex( pMapElement->FirstChildElement("tileset") );

	if ( !pTileSetIndex )
		ThrowRuntimeException("Failed to find element tileset in xml file, " + mFile)

	unsigned int gid, tileWidthSize, tileHeightSize, imageWidthSize, imageHeightSize;

	string tileSetName;
	string texFile;

	unique_ptr< TileMapSet > pTileMapSet;

	while( pTileSetIndex )
		{

		if ( pTileSetIndex->QueryUnsignedAttribute("firstgid", &gid) )
			ThrowRuntimeException("Failed to find attribute firstgid in xml file, " + mFile)

		pStr = pTileSetIndex->Attribute("name");

		if ( !pStr )
			ThrowRuntimeException("Failed to find attribute name in xml file, " + mFile)

		tileSetName = pStr;
		ToPlatformPath(tileSetName);

		if ( pTileSetIndex->QueryUnsignedAttribute("tilewidth", &tileWidthSize) )
			ThrowRuntimeException("Failed to find attribute tileWidth in xml file, " + mFile)

		if ( pTileSetIndex->QueryUnsignedAttribute("tileheight", &tileHeightSize) )
			ThrowRuntimeException("Failed to find attribute tileheight in xml file, " + mFile)

		// Load image element and attribute data
		XMLElement * pImageElement( pTileSetIndex->FirstChildElement("image") );

		if ( !pImageElement )
			ThrowRuntimeException("Failed to find element image in xml file, " + mFile)

		pStr = pImageElement->Attribute("source");

		if ( !pStr )
			ThrowRuntimeException("Failed to find attribute source in xml file, " + mFile)

		texFile = "../Resources/Maps/";
		texFile += pStr;
		ToPlatformPath(texFile);

		if ( pImageElement->QueryUnsignedAttribute("width", &imageWidthSize) )
			ThrowRuntimeException("Failed to find attribute width in xml file, " + mFile)

		if ( pImageElement->QueryUnsignedAttribute("height", &imageHeightSize) )
			ThrowRuntimeException("Failed to find attribute height in xml file, " + mFile)

		// Add data loaded for this tile set, construct class and insert into vector

		pTileMapSet.reset( new TileMapSet( texFile, gid, tileSetName, tileWidthSize, tileHeightSize, imageWidthSize, imageHeightSize ) );

		mTileSets.push_back( std::move( pTileMapSet ) );

		// Advance to next tileset element
		pTileSetIndex = pTileSetIndex->NextSiblingElement("tileset");
		}

	// Load layer elements and attribute data
	XMLElement * pMapLayerIndex( pMapElement->FirstChildElement("layer") );

	if ( !pMapLayerIndex )
		ThrowRuntimeException("Failed to find element layer in xml file, " + mFile)

	unsigned int layerTileWidthCount, layerTileHeightCount;
	unique_ptr< TileMapLayer > pTileMapLayer;
	unique_ptr< MapEntity > pMapEntity;
	string layerName;
	sf::Vector2f pos;
	while ( pMapLayerIndex )
		{
		pStr = pMapLayerIndex->Attribute("name");

		if ( !pStr )
			ThrowRuntimeException("Failed to find attribute name in xml file, " + mFile)

		layerName = pStr;

		if ( pMapLayerIndex->QueryUnsignedAttribute("width", &layerTileWidthCount) )
			ThrowRuntimeException("Failed to find attribute width in xml file, " + mFile)

		if ( pMapLayerIndex->QueryUnsignedAttribute("height", &layerTileHeightCount) )
			ThrowRuntimeException("Failed to find attribute height in xml file, " + mFile)

		pTileMapLayer.reset( new TileMapLayer(layerName, layerTileWidthCount, layerTileHeightCount) );

		// Load data element and attribute data
		XMLElement * pData( pMapLayerIndex->FirstChildElement("data"));

		if ( !pData )
			ThrowRuntimeException("Failed to find element data in xml file, " + mFile)


		// Load tile elements and attribute data
		// these are the sprite tiles
		XMLElement * pTile( pData->FirstChildElement("tile") );

		if ( !pTile )
			ThrowRuntimeException("Failed to find element tile in xml file, " + mFile)

		unsigned int count = 0;

		while (pTile)
			{
			if ( pTile->QueryUnsignedAttribute("gid", &gid) )
				ThrowRuntimeException("Failed to find attribute gid in xml file, " + mFile)

			if ( gid )
				{
				const TileMapSet * pTileMapSet( GetTileMapSetFromGid(gid) );

				if ( pTileMapSet )
					{
					pos.x = count % layerTileWidthCount * mTileWidthSize;
					pos.y = count / layerTileHeightCount * mTileHeightSize;

					pMapEntity.reset( new MapEntity( pTileMapSet->GetTexture(), pTileMapSet->GetTextureRect(gid), pos ) );

					pTileMapLayer->AddEntity( std::move(pMapEntity) );
					}
				}

			++count;
			pTile = pTile->NextSiblingElement("tile");
			}

		// push after loop so you still have access to pointer
		mTileMapLayers.push_back( std::move(pTileMapLayer) );

		pMapLayerIndex = pMapLayerIndex->NextSiblingElement("layer");
		}
	}

void TileMap::Update()
	{

	}

void TileMap::Draw(sf::RenderWindow * pWindow) const
	{
	for ( const unique_ptr< TileMapLayer > & pTileMapLayer : mTileMapLayers )
		{
		pTileMapLayer->Draw(pWindow);
		}
	}

const TileMapSet * TileMap::GetTileMapSetFromGid(const unsigned int gid) const
	{
	// Loops backwards so that the < check can be used
	for ( auto riter = mTileSets.rbegin(); riter != mTileSets.rend(); ++riter )
		{
		if ( gid < (*riter)->GetFirstGid() )
			continue;

		return (*riter).get();
		}

	return nullptr;
	}

// TileMapLayer

TileMapLayer::TileMapLayer(const string &layerName, unsigned int tileWidthCount, unsigned int tileHeightCount)
	:
	mLayerName( layerName ),
	mTileWidthCount( tileWidthCount ),
	mTileHeightCount( tileHeightCount )
	{

	}

TileMapLayer::~TileMapLayer()
	{

	}

void TileMapLayer::Update()
	{

	}

void TileMapLayer::Draw(sf::RenderWindow * pWindow) const
	{
	for ( const unique_ptr< MapEntity > & pEntity : mTileEntities )
		{
		pEntity->Draw(pWindow);
		}
	}

unsigned int TileMapLayer::GetTileWidthCount() const
	{
	return mTileWidthCount;
	}

unsigned int TileMapLayer::GetTileHeightCount() const
	{
	return mTileHeightCount;
	}

void TileMapLayer::AddEntity(unique_ptr<MapEntity> pEnt)
	{
	mTileEntities.push_back(std::move(pEnt));
	}

TileMapSet::TileMapSet(const std::string &texFile, unsigned int firstGid, const std::string &tileSetName, unsigned int tileWidthSize, unsigned int tileHeightSize, unsigned int imageWidthSize, unsigned int imageHeightSize)
	:
	mFirstGid(firstGid),
	mTileSetName(tileSetName),
	mTileWidthSize(tileWidthSize),
	mTileHeightSize(tileHeightSize),
	mImageWidthSize( imageWidthSize ),
	mImageHeightSize( imageHeightSize ),
	mTileWidthCount( mImageWidthSize / mTileWidthSize ),
	mTileHeightCount( mImageHeightSize / mTileHeightSize ),
	mpTexture( new sf::Texture() ),
	mTextureFile(texFile)
	{
	if ( !mpTexture->loadFromFile( texFile.c_str() ) )
		ThrowRuntimeException("Failed to load texture for map, " + texFile)

	}

unsigned int TileMapSet::GetFirstGid() const
	{
	return mFirstGid;
	}

unsigned int TileMapSet::GetWidthCount() const
	{
	return mTileWidthCount;
	}

unsigned int TileMapSet::GetHeightCount() const
	{
	return mTileHeightCount;
	}

sf::Texture & TileMapSet::GetTexture() const
	{
	return *(mpTexture.get());
	}

sf::IntRect TileMapSet::GetTextureRect(unsigned int gid) const
	{
	// Builds rect based on 2d cordinate system
	unsigned int zeroBasedGid( gid - mFirstGid );
	sf::IntRect rect;
	rect.left = zeroBasedGid % mTileWidthCount * mTileWidthSize;
	rect.top = (zeroBasedGid / mTileWidthCount) * mTileHeightSize;
	rect.width = mTileWidthSize;
	rect.height = mTileHeightSize;
	return rect;
	}
