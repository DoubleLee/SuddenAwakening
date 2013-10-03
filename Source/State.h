#ifndef STATE_H
#define STATE_H

#include <string>
#include <memory>
#include <vector>
using std::string;
using std::unique_ptr;
using std::vector;

enum class StateID : unsigned int
	{
	NullID = 0,
	SplashMovieID,
	MainMenuID,
	GamePlayID
	};

namespace sf
{
class Music;
class Texture;
class Sprite;
class Event;
}

class Game;
class AudioEffects;

namespace tinyxml2
{
class XMLElement;
}
using tinyxml2::XMLElement;

class State
{
public:
	State(const StateID stateID );
	virtual ~State();

	StateID GetID() const;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void LoadFromXML( const string & file ) = 0;
	virtual void ProcessEvent( const sf::Event & event );
private:
	StateID mID;

protected:
	virtual void LoadTexturesFromXML( XMLElement * pTexturesElement );
	virtual void LoadMusicFromXML( XMLElement * pMusicElement );
	virtual void LoadAudiosFromXML( XMLElement * pAudiosElement );
	//virtual void LoadSpitesFromXML( XMLElement * pSpritesElement );

	Game * mpGame;

	vector<sf::Texture> mTextures;
	unique_ptr<sf::Music> mpMusic;
	unique_ptr<AudioEffects> mpAudioEffects;
	unique_ptr<sf::Sprite> mpBackground;
};

#endif // STATE_H
