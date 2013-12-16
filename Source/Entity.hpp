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

/**
 * @brief The Entity class, represents a basic entity that exists in the 2d world.
 *
 * This class should be inherited from, to build complex types of objects that exist in the game world.
 *
 * For example the player, enemies, pick up items, keys, doors, ect...
 *
 * It can be drawable or non drawable.  It can be a position that things may spawn on.
 */
class Entity
{
public:
	/**
	 * @brief Entity ctor for making an entity.
	 * @param texture The texture to use for this objects when drawing.
	 * @param pos The position, usually in top left corner.
	 * @param collidable Whether this object can be collided.
	 */
	Entity( const sf::Texture & texture, const sf::Vector2f & pos, bool collidable = false);

	/**
	 * @brief ~Entity virtual call to destruct entities.
	 */
	virtual ~Entity();

	/**
	 * @brief Update virtual call to update entities, and their child class.
	 */
	virtual void Update();

	/**
	 * @brief Draw to a window.
	 * @param pWindow The window to draw to.
	 */
	virtual void Draw( sf::RenderWindow * pWindow );

	/**
	 * @brief SetIsCollidable setter for the collidable flag.
	 * @param collidable The value to set for collidable.
	 */
	void SetIsCollidable( bool collidable );

	/**
	 * @brief GetIsCollidable getter for the collidable flag.
	 * @return The current value for collidable.
	 */
	bool GetIsCollidable() const;

	/**
	 * @brief SetIsSpawnable setter for the spawnable flag.
	 * @param spawnable The value to set for spawnable.
	 */
	void SetIsSpawnable( bool spawnable );

	/**
	 * @brief GetIsSpawnable getter for the spawnable flag.
	 * @return The current value for spawnable.
	 */
	bool GetIsSpawnable() const;

	/**
	 * @brief GetPosition getter for the position of the sprite, usually in top left corner.
	 * @return The current position.
	 */
	const sf::Vector2f & GetPosition();

	/**
	 * @brief GetGlobalRect getter for the rectangle that borders the sprite.
	 * @return The rectangle of this object's sprite, in global coordinates.
	 */
	const sf::FloatRect & GetGlobalRect();

	/**
	 * @brief GetSprite getter for the sf::Sprite this Entity represents.
	 * @return The sprite this Entity represents.
	 */
	sf::Sprite * GetSprite();

protected:
	unique_ptr<sf::Sprite> mpSprite;
	bool mIsCollidable;
	bool mIsSpawnable;
};


/**
 * @brief The AnimatedEntity class, unfinished, maybe not used and/or deleted later.
 */
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

/**
 * @brief The Player class, is the class that holds the data for the player.
 *
 * It inherits from Entity
 *
 * This class is capable of animating itself.  It can be moved around the screen.
 * Other than that not much else functionality.
 *
 * The animation works by tracking the frames in x and y.
 *
 * You then multiply the tile size by the coordinate frame.  So xCoord * tileSize = position of frame in x on the texture.
 */
class Player : public Entity
{
public:
	/**
	 * @brief Player ctor.
	 * @param texture The sf::Texture to use as the players representation.
	 * @param pos The initial position of the player.
	 */
	Player( const sf::Texture & texture, const sf::Vector2f & pos );

	/**
	 * @brief ~Player virtual call to dtor.
	 */
	virtual ~Player();

	/**
	 * @brief Update, currently empty.
	 */
	virtual void Update();

	/**
	 * @brief UpdateControls is empty, code moved to Level class.
	 */
	virtual void UpdateControls();

	/**
	 * @brief GetXCoord getter for the x coordinate of the current frame.
	 * @return The current x frame coordinate.
	 */
	int GetXCoord() const;

	/**
	 * @brief SetXCoord setter for the x coordinate of the current frame.
	 * @param xCoord The value to set as the new frame.
	 */
	void SetXCoord(int xCoord);

	/**
	 * @brief GetYCoord getter for the y coordinate of the current frame.
	 * @return The current y frame coordinate.
	 */
	int GetYCoord() const;

	/**
	 * @brief SetYCoord
	 * @param yCoord
	 */
	void SetYCoord(int yCoord);

	/**
	 * @brief GetXDirection getter for the direction of the animation either +- 1 to indicate direction.
	 * @return The value to indicate animation direction.
	 */
	int GetXDirection() const;

	/**
	 * @brief SetXDirection setter for the direction of the animation either +- 1 to indicate direction.
	 * @param xDirection The value to set as the animation direction.
	 */
	void SetXDirection(int xDirection);

	/**
	 * @brief GetTextureSheetWidth getter for the texture sheets width.
	 * @return The texture sheets width.
	 */
	int GetTextureSheetWidth() const;

	/**
	 * @brief GetTextureSheetHeight getter for the texture sheets height.
	 * @return The texture sheets height.
	 */
	int GetTextureSheetHeight() const;

	/**
	 * @brief GetNextFrameTrigger get the time until the next frame should be displayed.
	 * @return The time until the next frame should be displayed.
	 */
	TimeInt GetNextFrameTrigger() const;

	/**
	 * @brief SetNextFrameTrigger setter for the time until the next frame should be displayed.
	 * @param trigger The time until the next frame should be displayed.
	 */
	void SetNextFrameTrigger(TimeInt trigger);

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
