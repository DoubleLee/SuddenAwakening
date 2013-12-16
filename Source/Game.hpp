#pragma once

#ifndef GAME_H
#define GAME_H

#include "State.hpp"

#include <memory>
using std::unique_ptr;

// States
namespace NewState
{
enum NewState
	{
	NullState = 0,
	MainMenu,
	GamePlay
	};
}

// Forward Declarations
namespace sf
{
class RenderWindow;
class Texture;
class Font;
class Shader;
class SoundBuffer;
}

class IState;
class ConfigLoader;

typedef unsigned long long TimeInt;

/**
 * @brief The Game class everything for this game starts here.
 *
 * This is the big class that everything should be within.
 *
 * It tracks time progression fps.
 *
 * This class is responsible for making the window, creating the music functionality and some fonts ( used by the Buttons ).
 *
 * It also stores a State pointer which is how we handle states.
 *
 * The State children are the real states.
 *
 * This class manages a singleton, you can access it through Game::Get()
 */
class Game
{
public:
	/**
	 * @brief Game only sets default values and tracks the singleton.
	 */
	Game();

	/**
	 * @brief ~Game dtor.
	*/
	~Game();

	/**
	 * @brief Init all game/engine initialization starts here.
	 * @return Success or fail of initialization of the entire game.
	 */
	bool Init();

	/**
	 * @brief Run is where all the game loop code is location and starts.
	 * @return The value that should be returned to the operating system to denote success or failure.
	 */
	int Run();

	/**
	 * @brief SetNewStateEnum is the setter for the enum to tell the Game to switch states on the next frame.
	 * @param stateID The value which represents a new state to change to.
	 */
	void SetNewStateEnum( StateID stateID );

	/**
	 * @brief Get is the singleton getter.
	 * @return Pointer to the Game singleton.
	 */
	static Game * Get();

	/**
	 * @brief GetWindow getter for the render window.
	 * @return Pointer to the render window for the game.
	 */
	sf::RenderWindow * GetWindow();

	/**
	 * @brief GetButtonFont getter for the font to be used with the buttons.
	 * @return The font to use for buttons.
	 */
	const sf::Font & GetButtonFont() const;

	/**
	 * @brief GetMusic
	 * @return
	 */
	sf::Music * GetMusic() const;

	const State * GetState() const;

	int GetMapTileSize() const;

	double GetFrameStampD() const;
	double GetFrameDeltaD() const;
	TimeInt GetFrameStampInt() const;
	TimeInt GetFrameDeltaInt() const;

	const string & GetTitleStr() const;

private:

	void ChangeStateCheck();
	void UpdateTimers();

	int mMapTileSize;

	unique_ptr<sf::RenderWindow> mpWindow;

	unique_ptr<sf::Font> mpFontButton;

	unique_ptr<sf::Music> mpMusic;

	unique_ptr<State> mpState;

	StateID mNewState;

	int mReturnValue;

	double mFrameStampD;
	double mFrameDeltaD;
	TimeInt mFrameStampInt;
	TimeInt mFrameDeltaInt;

	string mTitleString;

	static Game * mpsGame;
};

#endif // GAME_H
