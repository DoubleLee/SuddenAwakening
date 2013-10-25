#include "StateGamePlay.hpp"

#include "Game.hpp"
#include "LevelOne.hpp"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

StateGamePlay::StateGamePlay()
	:
	State( StateID::GamePlayID )
	{
	LoadNewGame();
	}

StateGamePlay::~StateGamePlay()
	{

	}

void StateGamePlay::Update()
	{
	if ( mpLevel )
		mpLevel->Update();
	}

void StateGamePlay::Draw()
	{
	if ( mpLevel )
		mpLevel->Draw();
	}

void StateGamePlay::LoadFromXML(const string & file)
	{

	}

void StateGamePlay::ProcessEvent(const sf::Event & event)
	{
	if ( event.type == sf::Event::KeyPressed )
		{
		if ( event.key.code == sf::Keyboard::Escape )
			{
			mpGame->SetNewStateEnum( StateID::MainMenuID );
			}
		}
	}

void StateGamePlay::LoadNewGame()
	{
	mpLevel.reset( new LevelOne() );
	}
