#include "StateGamePlay.hpp"

#include "Game.hpp"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

StateGamePlay::StateGamePlay()
	:
	State( StateID::GamePlayID )
	{

	}

StateGamePlay::~StateGamePlay()
	{

	}

void StateGamePlay::Update()
	{

	}

void StateGamePlay::Draw()
	{

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
			mpGame->SetChangeToState( StateID::MainMenuID );
			}
		}
	}
