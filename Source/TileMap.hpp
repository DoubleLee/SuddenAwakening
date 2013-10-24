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
}

class TileMapLayer;
class TileMapSet;

class TileMap
{
public:
	TileMap();
	void LoadFromFile( const std::string & file );
	virtual ~TileMap();

	virtual void Update();
	virtual void Draw() const;

	typedef std::pair< sf::Texture &, sf::IntRect > TilePair;

	TilePair GetTilePairFromGid( const unsigned int gid ) const;

protected:
	void LoadFromFile();
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
	TileMapLayer();
	virtual ~TileMapLayer();

	virtual void Update();
	virtual void Draw() const;


protected:
	vector< unique_ptr< Entity > > mTileEntities;
};


class TileMapSet
{
public:
	TileMapSet(const std::string & texFile, unsigned int firstGid, const std::string & tileSetName,
			   unsigned int tileWidthSize, unsigned int tileHeightSize,
			   unsigned int imageWidthSize, unsigned int imageHeightSize);

	unsigned int GetFirstGid();

protected:

	unsigned int mFirstGid;

	string mTileSetName;

	unsigned int mTileWidthSize;
	unsigned int mTileHeightSize;

	unsigned int mImageWidthSize;
	unsigned int mImageHeightSize;

	unsigned int mTilesWidthCount;
	unsigned int mTilesHeightCount;

private:
	unique_ptr< sf::Texture > mpTexture;
	string mTextureFile;
};

#endif // TILEMAP_HPP
