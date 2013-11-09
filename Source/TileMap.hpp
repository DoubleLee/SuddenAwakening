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

	unsigned int GetTileWidthCount() const;
	unsigned int GetTileHeightCount() const;

	void AddEntity( unique_ptr<MapEntity> pEnt );

protected:

	string mLayerName;

	unsigned int mTileWidthCount;
	unsigned int mTileHeightCount;

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

private:
	unique_ptr< sf::Texture > mpTexture;
	string mTextureFile;
};

#endif // TILEMAP_HPP
