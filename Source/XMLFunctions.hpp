#pragma once

#ifndef XMLFUNCTIONS_HPP
#define XMLFUNCTIONS_HPP

#include <vector>
#include <memory>

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
class Entity;
class Level;

template <typename Type> class ResourceManager;

/**
 * @brief LoadTexturesFromXML loads from xml into a ResourceManager a set of textures.
 * @param textures The resource manager to load the textures into
 * @param pTexturesElement The Textures element in xml to load from.
 */
void LoadTexturesFromXML( ResourceManager<sf::Texture> & textures, XMLElement * pTexturesElement );

/**
 * @brief LoadMusicFromXML loads music information from the xml element passed in.
 * @param music The sfml2 music class to load the music into.
 * @param pMusicElement The xml Music element for loading.
 */
void LoadMusicFromXML( sf::Music & music, XMLElement * pMusicElement );

/**
 * @brief LoadAudiosFromXML loads audo effects into the class from an xml Audios element.
 * @param audioMan The audio effect manager to load the audio buffers into.
 * @param pAudiosElement The xml Audios element for loading.
 */
void LoadAudiosFromXML( AudioEffects & audioMan, XMLElement * pAudiosElement );
//void LoadMapTilesFromXML( Level * pLevel, XMLElement * pMapElement );

#endif // XMLFUNCTIONS_HPP
