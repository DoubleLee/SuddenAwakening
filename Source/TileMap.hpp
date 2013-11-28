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

class TileMap
{
public:
	TileMap( const std::string & file );
	virtual ~TileMap();

	virtual void Update();
	virtual void Draw( sf::RenderWindow * pWindow ) const;
	virtual bool IsValidPosition( sf::Sprite * pSprite ) const;

	virtual const TileMapLayer * GetDataLayer() const;

protected:
	void LoadFromFile();
	const TileMapSet * GetTileMapSetFromGid( const unsigned int gid) const;
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

class TileMapLayer
{
public:
	TileMapLayer( const string & layerName, unsigned int tileWidthCount, unsigned int tileHeightCount);
	virtual ~TileMapLayer();

	virtual void Update();
	virtual void Draw(sf::RenderWindow * pWindow) const;

	virtual bool IsColliding( sf::Sprite * pSprite ) const;

	unsigned int GetTileWidthCount() const;
	unsigned int GetTileHeightCount() const;

	void SetIsVisible( bool visible );
	bool GetIsVisible() const;

	void AddEntity( unique_ptr<MapEntity> pEnt );

protected:

	string mLayerName;

	unsigned int mTileWidthCount;
	unsigned int mTileHeightCount;

	bool mIsVisible;

	vector< unique_ptr< MapEntity > > mTileEntities;
};


class TileMapSet
{
public:
	TileMapSet(const std::string & texFile, unsigned int firstGid, const std::string & tileSetName,
			   unsigned int tileWidthSize, unsigned int tileHeightSize,
			   unsigned int imageWidthSize, unsigned int imageHeightSize);

	unsigned int GetFirstGid() const;

	unsigned int GetWidthCount() const;
	unsigned int GetHeightCount() const;

	void SetIndexCollidable( int index );
	int GetIndexCollidable() const;

	void SetIndexSpawnable( int index );
	int GetIndexSpawnable() const;

	sf::Texture & GetTexture() const;
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
