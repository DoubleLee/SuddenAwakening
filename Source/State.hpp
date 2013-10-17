#pragma once

#ifndef STATE_H
#define STATE_H

#include <string>
#include <memory>
#include <vector>
using std::string;
using std::unique_ptr;
using std::vector;

#include "ResourceManager.hpp"

enum class StateID : unsigned int
	{
	NullID = 0,
	SplashMovieID,
	MainMenuID,
	GamePlayID
	};

namespace sf
{
class Music;
class Texture;
class Sprite;
class Event;
class Text;
class Font;
}

class Game;
class AudioEffects;



class State
{
public:
	State(const StateID stateID );
	virtual ~State();

	StateID GetID() const;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void LoadFromXML( const string & file ) = 0;
	virtual void ProcessEvent( const sf::Event & event ) = 0;
private:
	StateID mID;

protected:

	Game * mpGame;

	ResourceManager<sf::Texture> mTextures;
	unique_ptr<AudioEffects> mpAudioEffects;
	unique_ptr<sf::Sprite> mpBackground;
};

#endif // STATE_H
