#include "Level.hpp"

#include "Game.hpp"
#include "AudioEffects.hpp"
#include "Entity.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

Level::Level(LevelID levelID)
	:
	mID(levelID),
	mpGame( Game::Get() ),
	mpAudioEffects( new AudioEffects() ),
	mpLayerImage( new sf::Texture() )
	{

	}

Level::~Level()
	{

	}

LevelID Level::GetID() const
	{
	return mID;
	}
