#include "Entity.hpp"

#include "Game.hpp"
#include "StateGamePlay.hpp"

#include <SFML/Graphics.hpp>


// class Entity

Entity::Entity(const sf::Texture &texture, const sf::Vector2f &pos, bool collidable)
	:
	mpSprite( new sf::Sprite( texture ) ),
	mIsCollidable(collidable)
	{
	mpSprite->setPosition(pos);
	}

Entity::~Entity()
	{

	}

void Entity::Update()
	{

	}

void Entity::Draw(sf::RenderWindow * pWindow)
	{
	pWindow->draw( *(mpSprite.get()) );
	}


const sf::Vector2f & Entity::GetPosition()
	{
	return mpSprite->getPosition();
	}

const sf::FloatRect & Entity::GetGlobalRect()
	{
	return mpSprite->getGlobalBounds();
	}

sf::Sprite * Entity::GetSprite()
	{
	return mpSprite.get();
	}

void Entity::SetIsCollidable(bool collidable)
	{
	mIsCollidable = collidable;
	}

bool Entity::GetIsCollidable() const
	{
	return mIsCollidable;
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

	TimeInt time = pGame->GetFrameDeltaInt();
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
	}

int Player::GetXCoord() const
	{
	return mXcoord;
	}

void Player::SetXCoord(int xCoord)
	{
	mXcoord = xCoord;
	}

int Player::GetYCoord() const
	{
	return mYcoord;
	}

void Player::SetYCoord(int yCoord)
	{
	mYcoord = yCoord;
	}

int Player::GetXDirection() const
	{
	return mXDirection;
	}

void Player::SetXDirection(int xDirection)
	{
	mXDirection = xDirection;
	}

int Player::GetTextureSheetWidth() const
	{
	return mTextureSheetWidth;
	}

int Player::GetTextureSheetHeight() const
	{
	return mTextureSheetHeight;
	}

int Player::GetNextFrameTrigger() const
	{
	return mNextFrameTrigger;
	}

void Player::SetNextFrameTrigger(TimeInt trigger)
	{
	mNextFrameTrigger = trigger;
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
