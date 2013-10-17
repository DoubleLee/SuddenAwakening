#pragma once

#ifndef XMLFUNCTIONS_HPP
#define XMLFUNCTIONS_HPP

namespace tinyxml2
{
class XMLElement;
}
using tinyxml2::XMLElement;

namespace sf
{
class Music;
class Texture;
}

class AudioEffects;


template <typename Type> class ResourceManager;


void LoadTexturesFromXML( ResourceManager<sf::Texture> & textures, XMLElement * pTexturesElement );
void LoadMusicFromXML( sf::Music & music, XMLElement * pMusicElement );
void LoadAudiosFromXML( AudioEffects & audioMan, XMLElement * pAudiosElement );

#endif // XMLFUNCTIONS_HPP
