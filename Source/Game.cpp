#include "Game.hpp"

#include "Logger.hpp"
#include "ConfigLoader.hpp"
#include "StringUtilities.hpp"
#include "RandomGenerator.hpp"
#include "StateMainMenu.hpp"
#include "StateGamePlay.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

//#include "SFML/Graphics/RenderWindow.hpp"

#include <string>
#include <stdexcept>
#include <cassert>
#include <chrono>
using std::string;

// singleton
Game * Game::mpsGame = nullptr;

std::chrono::high_resolution_clock::time_point gGameStart;

Game::Game()
	:
	mpWindow(nullptr),
	mpState(nullptr),
	mNewState( StateID::MainMenuID ),
	mReturnValue(0),
	mFrameStampD(0.0f),
	mFrameDeltaD(0.0f),
	mFrameStamp(0),
	mFrameDelta(0)
	{
	if ( mpsGame )
		throw std::runtime_error("Two Game objects exist.");
	else
		mpsGame = this;

	gGameStart = std::chrono::high_resolution_clock::now();
	}

Game::~Game()
	{
	mpsGame = nullptr;
	}

Game * Game::Get()
	{
	return mpsGame;
	}

bool Game::Init()
	{
	LogFuncBegin();
	try
		{
		Random::Seed();
		string file;

		file = "../Resources/Scripts/GameConfig.xml";
		ConfigLoader config;

		config.LoadFromFile( ToPlatformPath( file ) );

		mpWindow.reset( new sf::RenderWindow(
						sf::VideoMode( config.GetScreenWidth(), config.GetScreenHeight() ),
						config.GetWindowTitle() ) );

		mTitleString = config.GetWindowTitle();
		mpFontButton.reset( new sf::Font( ) );

		if ( !mpFontButton->loadFromFile( config.GetFontButtonFile() ) )
			{
			throw std::runtime_error("Failed to load font");
			}

		mpState.reset( new StateMainMenu() );

		}
	catch ( std::exception & except )
		{
		LogFailure(except.what());
		return false;
		}

	LogFuncEndSuccess();
	return true;
	}

int Game::Run()
	{
	try
		{
		UpdateTimers();
		while ( mpWindow->isOpen() )
			{
			sf::Event event;
			while( mpWindow->pollEvent(event) )
				{
				if ( event.type == sf::Event::Closed )
					mpWindow->close();

				assert( mpState && mpWindow );
				mpState->ProcessEvent( event );
				}
			UpdateTimers();
			assert( mpState && mpWindow );
			mpState->Update();
			mpWindow->clear();
			mpState->Draw();
			mpWindow->display();

			if ( !ChangeState() )
				break; // failed to change state
			}
		}
	catch(std::exception & except)
		{
		LogFailure(except.what());
		}

	return mReturnValue;
	}

void Game::SetChangeToState(StateID stateID)
	{
	mNewState = stateID;
	}

bool Game::ChangeState()
	{
	if ( mNewState == mpState->GetID() )
		return true;

	if ( mNewState == StateID::MainMenuID )
		{
		mpState.reset(nullptr);
		mpState.reset( new StateMainMenu() );
		}

	if ( mNewState == StateID::GamePlayID )
		{
		mpState.reset(nullptr);
		mpState.reset( new StateGamePlay() );
		}

	return true;
	}

sf::RenderWindow * Game::GetWindow()
	{
	return mpWindow.get();
	}

const sf::Font & Game::GetButtonFont() const
	{
	return (*mpFontButton);
	}

void Game::UpdateTimers()
	{
	std::chrono::high_resolution_clock::time_point nowTime( std::chrono::high_resolution_clock::now() );
	std::chrono::microseconds sinceGameStart = std::chrono::duration_cast<std::chrono::microseconds> ( nowTime - gGameStart );
	mFrameDelta = sinceGameStart.count() - mFrameStamp;
	mFrameStamp = sinceGameStart.count();

	auto nowDouble = std::chrono::duration_cast< std::chrono::duration<double, std::ratio< 1, 1> > >(sinceGameStart);
	mFrameDeltaD = nowDouble.count() - mFrameStampD;
	mFrameStampD = nowDouble.count();
	}

double Game::GetFrameStampD() const
	{
	return mFrameStampD;
	}

double Game::GetFrameDeltaD() const
	{
	return mFrameDeltaD;
	}

TimeInt Game::GetFrameStamp() const
	{
	return mFrameStamp;
	}

TimeInt Game::GetFrameDelta() const
	{
	return mFrameDelta;
	}

const string & Game::GetTitleStr() const
	{
	return mTitleString;
	}
