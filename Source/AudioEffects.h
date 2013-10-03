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

	bool LoadBuffer( const string & file, AudioID audioID );

	weak_ptr<sf::Sound> PlaySound( AudioID audioID );

	void Update();

private:
	std::vector< shared_ptr< sf::Sound > > mActiveSounds;
	std::map< AudioID, std::vector<sf::SoundBuffer> > mAudioBuffers;
};

#endif // AUDIOEFFECTS_H
