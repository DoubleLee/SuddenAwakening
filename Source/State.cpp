#include "State.hpp"

#include "Logger.hpp"
#include "Game.hpp"
#include "StringUtilities.hpp"
#include "RandomGenerator.hpp"
#include "AudioEffects.hpp"

#include "tinyxml2.hpp"
using namespace tinyxml2;

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include <stdexcept>



State::State(const StateID stateID)
	:
	mID(stateID),
	mpGame(Game::Get()),
	mpAudioEffects( new AudioEffects() ),
	mpBackground( new sf::Sprite() )
	{

	}

State::~State()
	{

	}

StateID State::GetID() const
	{
	return mID;
	}

void State::ProcessEvent(const sf::Event & event)
	{

	}



