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

/**
 * @brief The AudioEffects class.
 *
 * This class manages sound buffers and effects that are in use by openAL.
 *
 * You can load audio files and associate them with an int ID.
 *
 * When a file is successfully loaded it you may play an instance of that sound by calling,
 * PlaySound( ID ), which returns a weak_ptr<sf::Sound> so you may modify its attributes
 * such as position.  It is safe to hold onto the weak_ptr but don't hold onto a shared_ptr from it.
 *
 * Sounds that have played through the entire buffer are ended.  They will be removed automatically.
 */
class AudioEffects
{
public:
	AudioEffects();

	/**
	 * @brief LoadBuffer is where you load a sound file into memory.
	 * @param file The file name and path to load.
	 * @param audioID The int ID to associate with this audio file.  Should be used to play the sound.
	 * @return Value to indicate if the file loaded successfully.
	*/
	bool LoadBuffer( const string & file, AudioID audioID );

	// Play a sound by id, also returns a weak_ptr to the sound
	// if you want to change a setting.  Never hold onto a shared_ptr
	// to one of these.
	weak_ptr<sf::Sound> PlaySound( AudioID audioID );

	/**
	 * @brief Update removes ended sounds from openAL.
	 */
	void Update();

	// immediately removes all sounds from the manager
	void ClearAll();

private:
	std::vector< shared_ptr< sf::Sound > > mActiveSounds;
	std::map< AudioID, std::vector<sf::SoundBuffer> > mAudioBuffers;
};

#endif // AUDIOEFFECTS_H
