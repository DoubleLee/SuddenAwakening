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

class Game
{
public:
	Game();
	~Game();

	bool Init();
	int Run();

	void SetNewStateEnum( StateID stateID );

	static Game * Get();

	sf::RenderWindow * GetWindow();

	const sf::Font & GetButtonFont() const;

	sf::Music * GetMusic() const;

	int GetMapTileSize() const;

	double GetFrameStampD() const;
	double GetFrameDeltaD() const;
	TimeInt GetFrameStamp() const;
	TimeInt GetFrameDelta() const;

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
	TimeInt mFrameStamp;
	TimeInt mFrameDelta;

	string mTitleString;

	static Game * mpsGame;
};

#endif // GAME_H
