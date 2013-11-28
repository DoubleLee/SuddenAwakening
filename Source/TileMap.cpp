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
	mFile(file),
	mFileVersion(0.0f),
	mTileWidthCount(0),
	mTileHeightCount(0),
	mTileWidthSize(0),
	mTileHeightSize(0),
	mpDataLayer(nullptr)
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
		{
		ThrowRuntimeException("Failed to find map element in xml file, " + mFile)
		}

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

		// Load properties for the map set.
		// TODO: change so that it loops over the properties
		XMLElement * pTileIndex = pTileSetIndex->FirstChildElement("tile");
		if ( pTileIndex )
			{
			int tileID = -1;
			if ( pTileIndex->QueryIntAttribute("id", &tileID) )
				{
				ThrowRuntimeException("Failed to find attribute id in xml file, " + mFile)
				}
			XMLElement * pPropertiesElement = pTileIndex->FirstChildElement("properties");
			if ( pPropertiesElement )
				{
				XMLElement * pPropertyElement = pPropertiesElement->FirstChildElement("property");
				if ( pPropertyElement )
					{

					const char * pStr = pPropertyElement->Attribute("name");
					if ( pStr )
						{
						string str = pStr;
						if ( str == "collidable" )
							{
							bool collidable;
							if ( !pPropertyElement->QueryBoolAttribute("value", &collidable) )
								{
								if ( collidable )
									{
									pTileMapSet->SetIndexCollidable( tileID );
									}
								}
							}
						if ( str == "spawnable" )
							{
							bool spawnable;
							if ( !pPropertyElement->QueryBoolAttribute("value", &spawnable) )
								{
								if ( spawnable )
									{
									pTileMapSet->SetIndexSpawnable( tileID );
									}
								}
							}
						}
					}
				}
			}

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
	bool visible = true;
	while ( pMapLayerIndex )
		{
		bool isDataLayer = false;
		pStr = pMapLayerIndex->Attribute("name");

		if ( !pStr )
			ThrowRuntimeException("Failed to find attribute name in xml file, " + mFile)

		layerName = pStr;

		if ( pMapLayerIndex->QueryUnsignedAttribute("width", &layerTileWidthCount) )
			ThrowRuntimeException("Failed to find attribute width in xml file, " + mFile)

		if ( pMapLayerIndex->QueryUnsignedAttribute("height", &layerTileHeightCount) )
			ThrowRuntimeException("Failed to find attribute height in xml file, " + mFile)

		pTileMapLayer.reset( new TileMapLayer(layerName, layerTileWidthCount, layerTileHeightCount) );


		XMLElement * pPropertiesElement = pMapLayerIndex->FirstChildElement("properties");

		if ( pPropertiesElement )
			{
			XMLElement * pPropIndex = pPropertiesElement->FirstChildElement("property");
			for ( ; pPropIndex ; pPropIndex = pPropIndex->NextSiblingElement("property") )
				{
				// load visible attribute, if not found then it defaults to true,
				// it's not an error if this attribute doesn't exist.
				const char * pName = pPropIndex->Attribute("name");
				if ( !pName )
					{
					ThrowRuntimeException("Failed to find name attribute in tile element")
					}
				string name = pName;
				if ( name == "visible" )
					{
					if ( pPropIndex->QueryBoolAttribute("value", &visible) == 0 )
						pTileMapLayer->SetIsVisible(visible);

					visible = true;
					}

				// check for data layer attribute
				// if found then set to TileMap's mpDataLayer field
				// if not found then do nothing, not an error
				if ( name == "isDataLayer" )
					{
					if ( pPropIndex->QueryBoolAttribute("value", &isDataLayer) == 0)
						{
						if ( isDataLayer )
							{
							mpDataLayer = pTileMapLayer.get();
							}
						}
					}
				}
			}

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
			bool collidable = false;
			bool spawn = false;
			if ( pTile->QueryUnsignedAttribute("gid", &gid) )
				ThrowRuntimeException("Failed to find attribute gid in xml file, " + mFile)

			if ( gid )
				{
				const TileMapSet * pTileMapSet = GetTileMapSetFromGid(gid);

				if ( pTileMapSet )
					{
					pos.x = count % layerTileWidthCount * mTileWidthSize;
					pos.y = count / layerTileHeightCount * mTileHeightSize;

					pMapEntity.reset( new MapEntity( pTileMapSet->GetTexture(), pTileMapSet->GetTextureRect(gid), pos ) );

					int collideIndex = pTileMapSet->GetIndexCollidable();

					if ( collideIndex > -1 )
						{
						if ( gid == collideIndex + pTileMapSet->GetFirstGid() )
							{
							pMapEntity->SetIsCollidable(true);
							}
						}

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
		if ( pTileMapLayer->GetIsVisible() )
			{
			pTileMapLayer->Draw(pWindow);
			}
		}
	}

bool TileMap::IsValidPosition(sf::Sprite * pSprite) const
	{
	return !( GetDataLayer()->IsColliding( pSprite ) );
	}

const TileMapLayer * TileMap::GetDataLayer() const
	{
	return mpDataLayer;
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
	mTileHeightCount( tileHeightCount ),
	mIsVisible(true)
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

bool TileMapLayer::IsColliding(sf::Sprite * pSprite) const
	{
	sf::FloatRect inRect = pSprite->getGlobalBounds();
	for ( const unique_ptr< MapEntity > & pEntity : mTileEntities )
		{
		// TODO: when Qt Creator works with unique_ptr remove this line and use the smart pointer directly
		MapEntity * pEnt = pEntity.get();
		sf::FloatRect entRect = pEnt->GetGlobalRect();
		if ( pEnt->GetIsCollidable() && entRect.intersects( inRect ) )
			return true;
		}
	return false;
	}

unsigned int TileMapLayer::GetTileWidthCount() const
	{
	return mTileWidthCount;
	}

unsigned int TileMapLayer::GetTileHeightCount() const
	{
	return mTileHeightCount;
	}

void TileMapLayer::SetIsVisible(bool visible)
	{
	mIsVisible = visible;
	}

bool TileMapLayer::GetIsVisible() const
	{
	return mIsVisible;
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
	mIndexCollidable(-1),
	mIndexSpawn(-1),
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

void TileMapSet::SetIndexCollidable(int index)
	{
	mIndexCollidable = index;
	}

int TileMapSet::GetIndexCollidable() const
	{
	return mIndexCollidable;
	}

void TileMapSet::SetIndexSpawnable(int index)
	{
	mIndexSpawn = index;
	}

int TileMapSet::GetIndexSpawnable() const
	{
	return mIndexSpawn;
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
