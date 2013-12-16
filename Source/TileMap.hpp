#pragma once
#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <string>
#include <vector>
#include <memory>
#include <utility>
using std::string;
using std::vector;
using std::unique_ptr;

#include "SFML/Graphics/Rect.hpp"

namespace sf
{
class Sprite;
class Texture;
class RenderWindow;
}

class MapEntity;

class TileMapLayer;
class TileMapSet;


/**
 * @brief The TileMap class presents the a map loaded from xml files from Tiled map editor.
 *
 * This can load a Tiled map from editor, via xml files.
 *
 * It must be in xml format.
 *
 * The ctor will load the map and if there is an error will throw an exception.
 *
 * Supports many layers, and many tile sets.
 */
class TileMap
{
public:

	/**
	 * @brief TileMap ctor, attempts to load the map file, throws exception if fails.
	 * @param file The file name and path to a map xml file.
	 */
	TileMap( const std::string & file );

	/**
	 * @brief ~TileMap virtual dtor.
	 */
	virtual ~TileMap();

	/**
	 * @brief Update currently empty.  Maybe something added in future.
	 *
	 * Such as animation for tiles. Or opening and closing doors.
	 */
	virtual void Update();

	/**
	 * @brief Draw will use sfml2 to draw the entire map with layers and transperancey
	 * @param pWindow The SFML2 window to draw to.
	 */
	virtual void Draw( sf::RenderWindow * pWindow ) const;

	/**
	 * @brief IsValidPosition is a check for collision.  This is how collisions with the map work.
	 * @param pSprite True if the position is valid, false if its colliding with something it shouldn't be.
	 * @return
	 */
	virtual bool IsValidPosition( sf::Sprite * pSprite ) const;

	/**
	 * @brief GetSpawnPosition getter for the spawn location.
	 * @return The coordinate for spawning as top left corner.
	 */
	virtual sf::Vector2f GetSpawnPosition( ) const;

	/**
	 * @brief GetDataLayer getter for the data layer which holds the data for collisions, spawns, ect..
	 * @return The map layer which is the data layer.
	 */
	virtual const TileMapLayer * GetDataLayer() const;

protected:

	/**
	 * @brief LoadFromFile private method for loading the tiled map from xml, can't be called outside this classes ctor.
	 */
	void LoadFromFile();

	/**
	 * @brief GetTileMapSetFromGid getter for the tile map set which the gid is in.  The gid represents a tile on the map.
	 * @param gid The tile ID.
	 * @return The map set which this id is on.
	 */
	const TileMapSet * GetTileMapSetFromGid( const unsigned int gid ) const;
	string mFile;

	float mFileVersion;
	string mOrientation;

	unsigned int mTileWidthCount;
	unsigned int mTileHeightCount;

	unsigned int mTileWidthSize;
	unsigned int mTileHeightSize;

	TileMapLayer * mpDataLayer;

	vector< unique_ptr< TileMapSet > > mTileSets;
	vector< unique_ptr< TileMapLayer > > mTileMapLayers;
};

/**
 * @brief The TileMapLayer class represents a layer on the map.  It can draw itself to the map.
 *
 * It's made up of the vector of entities which are on this layer.
 *
 * This class shouldn't be used by any devs directly, only within the TileMap class.
 */
class TileMapLayer
{
public:
	/**
	 * @brief TileMapLayer ctor builds the tile map layer.
	 * @param layerName The string name for this layer.
	 * @param tileWidthCount The count of tiles width.
	 * @param tileHeightCount The count of tiles height.
	 */
	TileMapLayer( const string & layerName, unsigned int tileWidthCount, unsigned int tileHeightCount);

	/**
	 * @brief ~TileMapLayer virtual call to dtor.
	 */
	virtual ~TileMapLayer();

	/**
	 * @brief Update currently empty.
	 */
	virtual void Update();

	/**
	 * @brief Draw uses sfml2 to draw the map layer's entities to the window.
	 * @param pWindow The window to draw to.
	 */
	virtual void Draw(sf::RenderWindow * pWindow) const;

	/**
	 * @brief IsColliding is a check to see if a sprite is colliding with any of the collidable Map layer Entities.
	 * @param pSprite The sprite to check against the map layer entities.
	 * @return True or False if is colliding with a collidable map layer entity.
	 */
	virtual bool IsColliding( sf::Sprite * pSprite ) const;

	/**
	 * @brief GetSpawnPosition looks for a entity that is spawnable then returns it's position.
	 * @return The position of the first found spawnable entity.
	 */
	virtual sf::Vector2f GetSpawnPosition() const;

	/**
	 * @brief GetTileWidthCount getter for the map layer tile width count.
	 * @return The map layer tile width count.
	 */
	unsigned int GetTileWidthCount() const;

	/**
	 * @brief GetTileHeightCount getter for the map layer tile height count.
	 * @return The map layer tile height count.
	 */
	unsigned int GetTileHeightCount() const;

	/**
	 * @brief SetIsVisible setter for the layers visible flag.
	 * @param visible The flag to set.
	 */
	void SetIsVisible( bool visible );

	/**
	 * @brief GetIsVisible getter for the layers visible flag.
	 * @return The visible flag.
	 */
	bool GetIsVisible() const;

	/**
	 * @brief AddEntity adds an entity to the vector of entities on this map.
	 * @param pEnt The entity to add.
	 */
	void AddEntity( unique_ptr<MapEntity> pEnt );

protected:

	string mLayerName;

	unsigned int mTileWidthCount;
	unsigned int mTileHeightCount;

	bool mIsVisible;

	vector< unique_ptr< MapEntity > > mTileEntities;
};

/**
 * @brief The TileMapSet class represents one image that is divided into many tiles.
 */
class TileMapSet
{
public:

	/**
	 * @brief TileMapSet ctor builds the set and loads the image into sfml texture.
	 * @param texFile The texture file name and path to load.
	 * @param firstGid The first gid on this tile set.
	 * @param tileSetName
	 * @param tileWidthSize
	 * @param tileHeightSize
	 * @param imageWidthSize
	 * @param imageHeightSize
	 */
	TileMapSet(const std::string & texFile, unsigned int firstGid, const std::string & tileSetName,
			   unsigned int tileWidthSize, unsigned int tileHeightSize,
			   unsigned int imageWidthSize, unsigned int imageHeightSize);

	/**
	 * @brief GetFirstGid getter for the first gid on this tile set.
	 * @return The first gid on this tile set.
	 */
	unsigned int GetFirstGid() const;

	/**
	 * @brief GetWidthCount getter for the width count of tiles on this image.
	 * @return The count of tiles on this image width.
	 */
	unsigned int GetWidthCount() const;

	/**
	 * @brief GetHeightCount getter for the height count of tiles on this image.
	 * @return The count of tiles on this image height.
	 */
	unsigned int GetHeightCount() const;

	/**
	 * @brief SetIndexCollidable setter for the index into this map set that is the collidable gid.
	 * The collidable gid is the firstGid + index.
	 * @param index The index that should be considered the collidable entity.
	 */
	void SetIndexCollidable( int index );

	/**
	 * @brief GetIndexCollidable getter for the index in this map set that is the collidable gid.
	 * The collidable gid is the firstGid + index.
	 * @return The index that is the collidable entity.
	 */
	int GetIndexCollidable() const;

	/**
	 * @brief SetIndexSpawnable setter for the index that is to be considered spawnable.
	 * The spawnable gid is the firstGid + index.
	 * @param index The index to be considered spawnable.
	 */
	void SetIndexSpawnable( int index );

	/**
	 * @brief GetIndexSpawnable getter for the index in this map set that is spawnable.
	 * The collidable gid is the firstGid + index.
	 * @return The index that is the spawnable entity.
	 */
	int GetIndexSpawnable() const;

	/**
	 * @brief GetTexture getter for the image/texture this map set represents.
	 * @return The sfml2 texture this map set contains.
	 */
	sf::Texture & GetTexture() const;

	/**
	 * @brief GetTextureRect getter for the texture rect that a gid represents.
	 * @param gid The gid of the rect you want.
	 * @return The int rect you requested.
	 */
	sf::IntRect GetTextureRect(unsigned int gid) const;

protected:

	unsigned int mFirstGid;

	string mTileSetName;

	unsigned int mTileWidthSize;
	unsigned int mTileHeightSize;

	unsigned int mImageWidthSize;
	unsigned int mImageHeightSize;

	unsigned int mTileWidthCount;
	unsigned int mTileHeightCount;

	int mIndexCollidable;
	int mIndexSpawn;

private:
	unique_ptr< sf::Texture > mpTexture;
	string mTextureFile;
};

#endif // TILEMAP_HPP
