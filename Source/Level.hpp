#pragma once

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "ResourceManager.hpp"

#include <memory>
#include <string>
#include <vector>
using std::string;
using std::unique_ptr;
using std::vector;

namespace sf
{
class Texture;
class Event;
}

enum class LevelID
	{
	LevelNull = 0,
	LevelOne,
	LevelTwo,
	LevelThree,
	};

class Game;
class AudioEffects;
class Entity;
class TileMap;
class Player;

namespace tinyxml2
{
class XMLElement;
}

class Level
{
friend void LoadMapTilesFromXML(Level*, tinyxml2::XMLElement*);
public:
	Level(LevelID levelID);
	virtual ~Level();

	LevelID GetID() const;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void LoadFromXML( const string & file ) = 0;
	virtual void ProcessEvent( const sf::Event & event ) = 0;

private:
	LevelID mID;

protected:
	Game * mpGame;

	ResourceManager<sf::Texture> mTextures;
	unique_ptr<AudioEffects> mpAudioEffects;
	unique_ptr< TileMap > mpTileMap;
	unique_ptr< Player > mpPlayer;
};

#endif // LEVEL_HPP
