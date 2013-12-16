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

/**
 * @brief The LevelID enum is a set of values for each level.
 */
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

/**
 * @brief The Level class represents everything required to have a level.
 *
 * It holds the TileMap class.  The Player class, an audio effects class and the textures class.
 *
 * This class is ment to be inherited from, with child classes adding to it's functionality for each level.
 */
class Level
{
friend void LoadMapTilesFromXML(Level*, tinyxml2::XMLElement*);
public:
	/**
	 * @brief Level ctor.
	 * @param levelID The ID for what level it is.
	 */
	Level(LevelID levelID);

	/**
	 * @brief ~Level virtual dtor.
	 */
	virtual ~Level();

	/**
	 * @brief GetID getter for the level ID.
	 * @return The level ID.
	 */
	LevelID GetID() const;

	/**
	 * @brief Update pure virtual call to a child class.
	 *
	 * This call is for updating the child classes.
	 */
	virtual void Update() = 0;

	/**
	 * @brief Draw pure virtual call to a child class.
	 *
	 * This call is for drawing the child classes.
	 */
	virtual void Draw() = 0;

	/**
	 * @brief UpdatePlayer is for updating the player code.
	 *
	 * This is where the player controls are updated and the animations.
	 */
	virtual void UpdatePlayer();

	/**
	 * @brief LoadFromXML is for loading levels from xml files.
	 * @param file File name and path to an xml file from Tiled map editor.
	 */
	virtual void LoadFromXML( const string & file ) = 0;

	/**
	 * @brief ProcessEvent is where operating system events are processsed.
	 * @param event The sfml event type for processing.
	 */
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
