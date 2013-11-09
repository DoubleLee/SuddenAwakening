#include "Entity.hpp"

#include "Game.hpp"

#include <SFML/Graphics.hpp>


// class Entity

Entity::Entity(const sf::Texture &texture, const sf::Vector2f &pos)
	:
	mpSprite( new sf::Sprite( texture ) )
	{
	mpSprite->setPosition(pos);
	}

Entity::~Entity()
	{

	}

const sf::Vector2f & Entity::GetPosition()
	{
	return mpSprite->getPosition();
	}

sf::Sprite * Entity::GetSprite()
	{
	return mpSprite.get();
	}

void Entity::Update()
	{

	}

void Entity::Draw(sf::RenderWindow * pWindow)
	{
	pWindow->draw( *(mpSprite.get()) );
	}

// class AnimatedEntity

AnimatedEntity::AnimatedEntity( const sf::Texture & texture, const sf::Vector2f & pos )
	:
	Entity(texture, pos)
	{

	}

AnimatedEntity::~AnimatedEntity()
	{

	}

void AnimatedEntity::Update()
	{
	Game * pGame = Game::Get();

	if ( !pGame )
		return;

	TimeInt time = pGame->GetFrameDelta();
	}

// class Player

Player::Player(const sf::Texture &texture, const sf::Vector2f &pos)
	:
	Entity(texture, pos),
	mXcoord(0),
	mYcoord(0),
	mXDirection(1),
	mTextureSheetWidth(32),
	mTextureSheetHeight(32),
	mNextFrameTrigger(0)
	{
	// TODO: figure out a better way to get tile size (32), should not ever use constants.
	sf::Vector2u size = texture.getSize();

	if ( size.x % 32 || size.y % 32 )
		{
		ThrowRuntimeException("Players texture sheet frame size is not a multiple of 32")
		}

	if ( size.y / 32 != 4 )
		{
		//ThrowRuntimeException("Players texture sheet doesn't have all 4 directions.")
		}

	mTextureSheetWidth = size.x / 32;
	mTextureSheetHeight = size.y / 32;
	}

Player::~Player()
	{

	}

void Player::Update()
	{
	UpdateControls();
	}

void Player::UpdateControls()
	{
	Game * pGame = Game::Get();
	TimeInt now = pGame->GetFrameStamp();

	bool directionPressed = false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
		{
		mYcoord = static_cast<int>( Direction::Right );
		directionPressed = true;
		}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
		{
		mYcoord = static_cast<int>( Direction::Left );
		directionPressed = true;
		}


	if ( mNextFrameTrigger <= now )
		{

		if ( directionPressed )
			{
			mXcoord = mXcoord + mXDirection;
			if ( mXcoord >= mTextureSheetWidth )
				{
				mXDirection = -1;
				mXcoord = mTextureSheetWidth;
				}
			}
		else
			{
			mXDirection = -1;
			if ( mXcoord <= 0 )
				{
				mXDirection = 1;
				mXcoord = 0;
				}
			}

		mNextFrameTrigger = now + TimeInt(150000);
		}

	sf::IntRect rect;
	rect.top = mYcoord * 32;
	rect.left = mXcoord * 32;

	rect.height = 32;
	rect.width = 32;

	mpSprite->setTextureRect( rect );
	}

// class MapEntity

MapEntity::MapEntity( const sf::Texture & texture, const sf::IntRect & texRect, const sf::Vector2f & pos )
	:
	Entity(texture, pos)
	{
	mpSprite->setTextureRect(texRect);
	}

MapEntity::~MapEntity()
	{

	}
