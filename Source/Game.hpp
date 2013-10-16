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

	void SetChangeToState( StateID stateID );

	static Game * Get();

	sf::RenderWindow * GetWindow();

	const sf::Font & GetButtonFont() const;

	double GetFrameStampD() const;
	double GetFrameDeltaD() const;
	TimeInt GetFrameStamp() const;
	TimeInt GetFrameDelta() const;

	const string & GetTitleStr() const;

private:

	bool ChangeState();
	void UpdateTimers();

	unique_ptr<sf::RenderWindow> mpWindow;

	unique_ptr<sf::Font> mpFontButton;

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
