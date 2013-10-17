#pragma once

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "ResourceManager.hpp"

#include <memory>
#include <string>
using std::string;
using std::unique_ptr;

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

class Level
{
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

};

#endif // LEVEL_HPP
