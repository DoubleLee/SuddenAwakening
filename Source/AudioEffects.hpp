#pragma once

#ifndef AUDIOEFFECTS_H
#define AUDIOEFFECTS_H

enum class AudioID : int
	{
	BeginID = 0,
	BasicLaserID,
	MedLaserID,
	ClickID,
	// add new enum after this comment, not at the end
	EndID
	};

#include <map>
#include <string>
#include <vector>
#include <memory>
using std::shared_ptr;
using std::weak_ptr;
using std::string;

#include "SFML/Audio.hpp"

class AudioEffects
{
public:
	AudioEffects();

	// Loads a buffer into an id's buffer array
	bool LoadBuffer( const string & file, AudioID audioID );

	// Play a sound by id, also returns a weak_ptr to the sound
	// if you want to change a setting.  Never hold onto a shared_ptr
	// to one of these.
	weak_ptr<sf::Sound> PlaySound( AudioID audioID );

	// Remove ended sounds
	void Update();

	// immediately removes all sounds from the manager
	void ClearAll();

private:
	std::vector< shared_ptr< sf::Sound > > mActiveSounds;
	std::map< AudioID, std::vector<sf::SoundBuffer> > mAudioBuffers;
};

#endif // AUDIOEFFECTS_H
