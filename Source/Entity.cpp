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
	mMapTileSize(0),
	mNextFrameTrigger(0)
	{
	Game * pGame = Game::Get();
	mMapTileSize = pGame->GetMapTileSize();


	sf::Vector2u size = texture.getSize();

	if ( size.x % mMapTileSize || size.y % mMapTileSize )
		{
		ThrowRuntimeException("Players texture sheet frame size is not a multiple of 32")
		}

	if ( size.y / mMapTileSize != 4 )
		{
		ThrowRuntimeException("Players texture sheet doesn't have all 4 directions.")
		}

	mTextureSheetWidth = size.x / mMapTileSize;
	mTextureSheetHeight = size.y / mMapTileSize;
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
	float delta = float(pGame->GetFrameDeltaD());

	sf::Vector2f moveVec(0.0f,0.0f);
	float speed = mMapTileSize * 3.0f * delta;

	// set animation direction on Y cordinate of sheet
	bool directionPressed = false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
		{
		mYcoord = static_cast<int>( Direction::Right );
		moveVec.x += speed;
		directionPressed = true;
		}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
		{
		mYcoord = static_cast<int>( Direction::Left );
		moveVec.x -= speed;
		directionPressed = true;
		}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
		{
		mYcoord = static_cast<int>( Direction::Up );
		moveVec.y -= speed;
		directionPressed = true;
		}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
		{
		mYcoord = static_cast<int>( Direction::Down );
		moveVec.y += speed;
		directionPressed = true;
		}

	// move animation forward each time step
	if ( mNextFrameTrigger <= now )
		{
		// if a direction is pressed move the animation forward
		if ( directionPressed )
			{
			mXcoord += mXDirection;
			// check high side
			if ( mXcoord > (mTextureSheetWidth - 1) )
				{
				mXDirection = -1;
				mXcoord = (mTextureSheetWidth - 1) - 1;
				}
			// check low side
			if ( mXcoord < 0 )
				{
				mXDirection = 1;
				mXcoord = 1;
				}
			}
		else  // if no button is pressed change to first frame for standing
			{
			mXDirection = 1;
			mXcoord = 0;
			}

		// move the trigger forward
		mNextFrameTrigger = now + TimeInt(132000);
		}

	// calculate and set texture rect
	sf::IntRect rect;
	rect.top = mYcoord * mMapTileSize;
	rect.left = mXcoord * mMapTileSize;

	rect.height = mMapTileSize;
	rect.width = mMapTileSize;

	mpSprite->setTextureRect( rect );
	mpSprite->move( moveVec );
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
