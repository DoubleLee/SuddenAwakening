#include "Level.hpp"

#include "Game.hpp"
#include "AudioEffects.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

Level::Level(LevelID levelID)
	:
	mID(levelID),
	mpGame( Game::Get() ),
	mpAudioEffects( new AudioEffects() )
	{

	}

Level::~Level()
	{

	}

LevelID Level::GetID() const
	{
	return mID;
	}
