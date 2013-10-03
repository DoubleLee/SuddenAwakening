#include "AudioEffects.h"

#include "RandomGenerator.h"

#include <utility>
#include <stdexcept>



AudioEffects::AudioEffects()
	{

	}

void AudioEffects::Update()
	{
	// remove finished sounds
	for ( unsigned int i = 0; i < mActiveSounds.size(); )
		{
		if ( mActiveSounds[i]->getStatus() == sf::SoundSource::Stopped )
			{
			mActiveSounds.erase( mActiveSounds.begin() + i );
			}
		else
			{
			++i;
			}
		}
	}

bool AudioEffects::LoadBuffer(const string & file, AudioID audioID)
	{
	sf::SoundBuffer buffer;
	if ( !buffer.loadFromFile( file ) )
		{
		return false;
		}
	auto searchIter = mAudioBuffers.find( audioID );
	decltype( searchIter ) iter = searchIter;

	if ( searchIter == mAudioBuffers.end() )
		{
		auto successPair = mAudioBuffers.insert( std::make_pair( audioID, std::vector<sf::SoundBuffer> () ) );
		if ( !successPair.second )
			throw std::runtime_error("Failed to insert a new pair into audio buffer map");
		iter = successPair.first;
		}

	auto & vec = iter->second;
	vec.push_back( std::move(buffer) );
	return true;
	}

weak_ptr<sf::Sound> AudioEffects::PlaySound(AudioID audioID)
	{
	auto searchIter = mAudioBuffers.find( audioID );
	if ( searchIter == mAudioBuffers.end() )
		return weak_ptr<sf::Sound>();

	std::vector< sf::SoundBuffer> & buffers = searchIter->second;

	if ( buffers.empty() )
		return weak_ptr<sf::Sound>();

	int index = -1;
	if ( buffers.size() == 1 )
		{
		index = 0;
		}
	else
		{
		index = Random::Between(0, buffers.size() - 1);
		}

	shared_ptr<sf::Sound> pSound( new sf::Sound( buffers.at(index) ) );

	mActiveSounds.push_back(pSound);
	pSound->play();

	return weak_ptr<sf::Sound>(pSound);
	}
