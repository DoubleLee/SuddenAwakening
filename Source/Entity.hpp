#pragma once

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Game.hpp"

#include <memory>
using std::unique_ptr;

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"

namespace sf
{
class Sprite;
class Texture;
class RenderWindow;
}

class Entity
{
public:
	Entity( const sf::Texture & texture, const sf::Vector2f & pos);
	virtual ~Entity();

	virtual void Update();
	virtual void Draw( sf::RenderWindow * pWindow );

	const sf::Vector2f & GetPosition();
	const sf::FloatRect & GetGlobalRect();

	sf::Sprite * GetSprite();

protected:
	unique_ptr<sf::Sprite> mpSprite;
};

class AnimatedEntity : public Entity
{
public:
	AnimatedEntity( const sf::Texture & texture, const sf::Vector2f & pos );
	virtual ~AnimatedEntity();

	virtual void Update();
	//virtual void Draw( sf::RenderWindow * pWindow );
};

enum class Direction
	{
	Up = 0,
	Down,
	Left,
	Right
	};

class Player : public Entity
{
public:
	Player( const sf::Texture & texture, const sf::Vector2f & pos );
	virtual ~Player();

	virtual void Update();

	virtual void UpdateControls();

protected:
	int mXcoord;
	int mYcoord;

	int mXDirection;

	int mTextureSheetWidth;
	int mTextureSheetHeight;
	int mMapTileSize;
	TimeInt mNextFrameTrigger;
};

class MapEntity : public Entity
{
public:
	MapEntity( const sf::Texture & texture, const sf::IntRect & texRect, const sf::Vector2f & pos);
	virtual ~MapEntity();
};



#endif // ENTITY_HPP
