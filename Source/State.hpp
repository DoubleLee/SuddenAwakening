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

/**
 * @brief The StateID enum is the enum to represent a State type as integer values.
 *
 * Useful for telling the Game to change a state, or detecting the current state.
 */
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

/**
 * @brief The State class is the base class for states.
 *
 * This is meant to be inherited from, to create concrete state types.
 *
 * The states are for the different states the game maybe in.
 *
 * There are 4 pure virtual methods, Update and Draw are for updating and drawing of all the child states.
 *
 * LoadFromXML is for loading the states data, which should be unique to each state.
 *
 * ProcessEvent is where the states can become aware of operating system messages such as keypresses.
 *
 * Each state keeps track of the StateID which signifies what type of state it is.
 */
class State
{
public:
	/**
	 * @brief State ctor.
	 * @param stateID The enum to signify what type of state the child is.
	 */
	State(const StateID stateID );

	/**
	 * @brief ~State virtual dtor.
	 */
	virtual ~State();

	/**
	 * @brief GetID getter for the state id.
	 * @return This states ID.
	 */
	StateID GetID() const;

	/**
	 * @brief Update pure virtual call to update the child class.
	 */
	virtual void Update() = 0;

	/**
	 * @brief Draw pure virtual call to draw the child class.
	 */
	virtual void Draw() = 0;

	/**
	 * @brief LoadFromXML pure virtual call to load the child classes data from an xml file.
	 * @param file The file name and path to an xml file.
	 */
	virtual void LoadFromXML( const string & file ) = 0;

	/**
	 * @brief ProcessEvent pure virtual call, is where operating system events can be processed.
	 * @param event The sfml Event to be processed.
	 */
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
