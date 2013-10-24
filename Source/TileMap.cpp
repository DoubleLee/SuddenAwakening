#include "TileMap.h"

TileMap::TileMap( const std::string & file )
	:
	mFile(file)
	{
	LoadFromFile(file);
	}


