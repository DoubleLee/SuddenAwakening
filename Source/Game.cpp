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
#include "SFML/Audio.hpp"

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
	mpMusic(nullptr),
	mpState(nullptr),
	mNewState( StateID::MainMenuID ),
	mReturnValue(0),
	mFrameStampD(0.0f),
	mFrameDeltaD(0.0f),
	mFrameStamp(0),
	mFrameDelta(0)
	{
	if ( mpsGame )
		ThrowRuntimeException("Two Game objects exist.")
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

		mMapTileSize = config.GetMapTileSize();

		mpWindow.reset( new sf::RenderWindow(
						sf::VideoMode( config.GetScreenWidth(), config.GetScreenHeight() ),
						config.GetWindowTitle() ) );

		mTitleString = config.GetWindowTitle();
		mpFontButton.reset( new sf::Font( ) );

		if ( !mpFontButton->loadFromFile( config.GetFontButtonFile() ) )
			{
			ThrowRuntimeException( "Failed to load font, " + config.GetFontButtonFile() )
			}

		mpMusic.reset( new sf::Music() );

		mpState.reset( new StateMainMenu() );

		}
	catch ( std::exception & except )
		{
		gLogger.Exception(except);
		throw std::runtime_error(except.what());
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
				if ( event.type == sf::Event::Closed ) mpWindow->close();
				assert( mpState && mpWindow );
				mpState->ProcessEvent( event );
				}
			UpdateTimers();
			assert( mpState && mpWindow );
			mpState->Update();
			mpWindow->clear();
			mpState->Draw();
			mpWindow->display();

			ChangeStateCheck();
			}
		}
	catch(std::exception & except)
		{
		gLogger.Exception(except);
		}
	catch(...)
		{
		LogFailure("Unknown Error")
		}

	return mReturnValue;
	}

void Game::SetNewStateEnum(StateID stateID)
	{
	mNewState = stateID;
	}

void Game::ChangeStateCheck()
	{
	if ( mNewState == mpState->GetID() )
		return;

	if ( mNewState == StateID::MainMenuID )
		{
		mpState.reset(nullptr);
		mpState.reset( new StateMainMenu() );
		return;
		}

	if ( mNewState == StateID::GamePlayID )
		{
		mpState.reset(nullptr);
		mpState.reset( new StateGamePlay() );
		return;
		}

	ThrowRuntimeException("Failed to handle the new state enum, " + std::to_string( static_cast<int>(mNewState) ) )
	}

sf::RenderWindow * Game::GetWindow()
	{
	return mpWindow.get();
	}

const sf::Font & Game::GetButtonFont() const
	{
	return (*mpFontButton);
	}

sf::Music * Game::GetMusic() const
	{
	return mpMusic.get();
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

int Game::GetMapTileSize() const
	{
	return mMapTileSize;
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
