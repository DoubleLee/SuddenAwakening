#pragma once
#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::unique_ptr;

class TileMapLayer;

class TileMap
{
public:
	TileMap();
	void LoadFromFile( const std::string & file );
	virtual ~TileMap();

	sf::IntRect GetRectFromGid( const unsigned int gid ) const;

	std::vector< sf::Texture > mTextures;

protected:
	std::string mFile;
};

class TileMapLayer
{
public:
	TileMapLayer();
};

#endif // TILEMAP_HPP
