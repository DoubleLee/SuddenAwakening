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

void TileMap::LoadFromFile()
	{
	LoadFromFile(mFile);
	}

void TileMap::LoadFromFile( const std::string & file )
	{
	// Load Tiled map xml file
	XMLDocument doc;
	if ( doc.LoadFile(file.c_str()) )
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

		texFile = "../Resources/Maps/";
		texFile += pStr;
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

	XMLElement * pMapLayerIndex( pMapElement->FirstChildElement("layer") );


	if ( !pMapLayerIndex )
		ThrowRuntimeException("Failed to find element layer in xml file, " + file)

	unsigned int tileWidthCount, tileHeightCount;
	unique_ptr< TileMapLayer > pTileMapLayer;
	unique_ptr< Entity > pEntity;
	string layerName;
	sf::Vector2f pos;
	while ( pMapLayerIndex )
		{
		pStr = pMapLayerIndex->Attribute("name");

		if ( !pStr )
			ThrowRuntimeException("Failed to find attribute name in xml file, " + file)

		layerName = pStr;

		if ( pMapLayerIndex->QueryUnsignedAttribute("width", &tileWidthCount) )
			ThrowRuntimeException("Failed to find attribute width in xml file, " + file)

		if ( pMapLayerIndex->QueryUnsignedAttribute("height", &tileHeightCount) )
			ThrowRuntimeException("Failed to find attribute height in xml file, " + file)

		pTileMapLayer.reset( new TileMapLayer(layerName, tileWidthCount, tileHeightCount) );

		XMLElement * pData( pMapLayerIndex->FirstChildElement("data"));

		if ( !pData )
			ThrowRuntimeException("Failed to find element data in xml file, " + file)


		XMLElement * pTile( pData->FirstChildElement("tile") );

		if ( !pTile )
			ThrowRuntimeException("Failed to find element tile in xml file, " + file)

		unsigned int count = 0;

		while (pTile)
			{
			if ( pTile->QueryUnsignedAttribute("gid", &gid) )
				ThrowRuntimeException("Failed to find attribute gid in xml file, " + file)

			if ( gid )
				{
				const TileMapSet * pTileMapSet( GetTileMapSetFromGid(gid) );

				// NOTE: maybe use layers widthCount
				pos.x = count % mTileWidthCount * mTileWidthSize;
				pos.y = count / mTileHeightCount * mTileHeightSize;

				pEntity.reset( new Entity( pTileMapSet->GetTexture(), pTileMapSet->GetTextureRect(gid), pos ) );

				pTileMapLayer->AddEntity( std::move(pEntity) );
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

void TileMap::Draw() const
	{
	for ( const unique_ptr< TileMapLayer > & pTileMapLayer : mTileMapLayers )
		{
		pTileMapLayer->Draw();
		}
	}

const TileMapSet * TileMap::GetTileMapSetFromGid(const unsigned int gid) const
	{
	for ( auto riter = mTileSets.rbegin(); riter != mTileSets.rend(); ++riter )
		{
		if ( gid < (*riter)->GetFirstGid() )
			continue;

		return (*riter).get();
		}
	ThrowRuntimeException("Failed to find TileMapSet for gid, " + std::to_string(gid) )
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

void TileMapLayer::AddEntity(unique_ptr<Entity> pEnt)
	{
	mTileEntities.push_back(std::move(pEnt));
	}

void TileMapLayer::Update()
	{

	}

void TileMapLayer::Draw() const
	{
	sf::RenderWindow * pWindow(Game::Get()->GetWindow());

	for ( const unique_ptr< Entity > & pEntity : mTileEntities )
		{
		pEntity->Draw(pWindow);
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
	unsigned int zeroBasedGid( gid - mFirstGid );
	sf::IntRect rect;
	rect.left = zeroBasedGid % mTileWidthCount * mTileWidthSize;
	rect.top = (zeroBasedGid / mTileWidthCount) * mTileHeightSize;
	rect.width = mTileWidthSize;
	rect.height = mTileHeightSize;
	return rect;
	}
