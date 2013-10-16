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

template < class T >
bool IsValidEnum( T & enumRef, int valueID )
	{
	if ( valueID > static_cast<int>(T::BeginID) && valueID < static_cast<int>(T::EndID) )
		{
		enumRef = static_cast<T> (valueID);
		return true;
		}
	return false;
	}

State::State(const StateID stateID)
	:
	mID(stateID),
	mpGame(Game::Get())
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

void State::LoadTexturesFromXML(XMLElement * pTexturesElement)
	{
	// Make sure element passed in is valid, and the correct one.
	if ( !pTexturesElement || strcmp(pTexturesElement->Name(), "textures") )
		{
		throw std::runtime_error("LoadTexturesFromXML invalid node passed in");
		}

	// delete any textures old textures if there are any.
	mTextures.clear();

	// Get first texture element
	XMLElement * pTexIndex( pTexturesElement->FirstChildElement("texture") );

	// loop over each texture element and load them.
	string file;
	while ( pTexturesElement && pTexIndex )
		{
		// Create new sf::Texture at back of vector
		mTextures.emplace_back();
		sf::Texture & tex ( mTextures.back() );

		// Get texture file name and check for validity
		const char * pStr ( pTexIndex->Attribute("file") );
		if ( !pStr )
			{
			mTextures.pop_back();
			throw std::runtime_error("Failed to load texture file string.");
			}

		file = pStr;

		// Load texture into sfml and check for problems
		if ( !tex.loadFromFile( ToPlatformPath(file) ) )
			{
			mTextures.pop_back();
			throw std::runtime_error("Failed to load texture file " + file);
			}
		// Iterate to next texture element.
		pTexIndex = pTexIndex->NextSiblingElement("texture");
		}
	}

void State::LoadMusicFromXML(XMLElement * pMusicElement)
	{
	// Make sure element passed in is valid, and the correct one.
	if ( !pMusicElement || strcmp(pMusicElement->Name(), "music") )
		{
		throw std::runtime_error("Load music from xml, invalid node passed in.");
		}

	if ( !mpMusic )
		mpMusic.reset( new sf::Music() );

	// Get music file name attribute from element and check for error
	const char * pStr ( pMusicElement->Attribute("file") );
	if ( !pStr )
		throw std::runtime_error("No file attribute in music element, use empty string for no music");

	string file(pStr);

	if ( file.empty() )
		{
		throw std::runtime_error("Music file name is empty.");
		}

	// Tell sf::Music to load file and check for problems
	if ( !mpMusic->openFromFile(  ToPlatformPath( file ).c_str() ) )
		{
		throw std::runtime_error("Failed to load music file into sf::Music");
		}

	float volume ( 100.0f );

	// Get volume from music attribute and check for problems
	if ( pMusicElement->QueryFloatAttribute("volume", & volume) )
		{
		throw std::runtime_error("Failed to find volume in music element");
		}

	// setup sf::Music settings and play music
	mpMusic->setRelativeToListener(true);
	mpMusic->setVolume(volume);
	mpMusic->setLoop(true);
	mpMusic->play();
	}

void State::LoadAudiosFromXML(XMLElement * pAudiosElement)
	{
	// Make sure element passed in is valid, and the correct one.
	if ( !pAudiosElement || strcmp( pAudiosElement->Name(), "audios" ) )
		{
		throw std::runtime_error("Invalid element sent to LoadAudioFromXML");
		}

	mpAudioEffects.reset( new AudioEffects() );

	// Get first audio element
	XMLElement * pAudioIndex ( pAudiosElement->FirstChildElement("audio") );

	// Iterate over each audio element
	while ( pAudiosElement && pAudioIndex )
		{
		// Get file name for this audio and check for problems
		const char * pStr ( pAudioIndex->Attribute("file") );
		if ( !pStr )
			throw std::runtime_error("audio element has no file attribute");

		string file(pStr);

		int audioID = -1;

		// Get audioID from audio element and check for problems
		if ( pAudioIndex->QueryIntAttribute("audioID", &audioID) )
			{
			throw std::runtime_error("audio element has no audio id attribute");
			}

		AudioID id;

		// Template function to make sure the id is valid
		if ( !IsValidEnum(id, audioID) )
			{
			throw std::runtime_error("AudioID from audio element is not valid.");
			}

//		AudioID id( static_cast< AudioID > (audioID) );
//		if ( !(audioID < static_cast<int>( decltype(id)::LastID) && audioID > static_cast<int>(decltype(id)::FirstID) ) )
//			{
//			throw std::runtime_error("AudioID is not a valid id");
//			}

		// Load the audio into the AudioEffects manager in the id group
		if ( !mpAudioEffects->LoadBuffer( ToPlatformPath(file), id ) )
			{
			throw std::runtime_error("Failed while loading audio buffer file");
			}

		// Iterate to next audio element
		pAudioIndex = pAudioIndex->NextSiblingElement("audio");
		}
	}


