#include "Entity.hpp"

#include <SFML/Graphics.hpp>


Entity::Entity( const Texture & texture, const sf::IntRect & texRect, const sf::Vector2f & pos )
	:
	mpSprite( new Sprite(texture, texRect) )
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

Sprite * Entity::GetSprite()
	{
	return mpSprite.get();
	}

void Entity::Update()
	{

	}

void Entity::Draw(sf::RenderWindow *pWindow)
	{
	pWindow->draw( *(mpSprite.get()) );
	}
