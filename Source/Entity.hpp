#ifndef ENTITY_HPP
#define ENTITY_HPP

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
using sf::Sprite;
using sf::Texture;

class Entity
{
public:
	Entity( const Texture & texture, const sf::IntRect & texRect, const sf::Vector2f & pos);
	virtual ~Entity();

	virtual void Update();
	virtual void Draw( sf::RenderWindow * pWindow );

	const sf::Vector2f & GetPosition();
	const sf::FloatRect & GetGlobalRect();

	Sprite * GetSprite();

protected:
	unique_ptr<Sprite> mpSprite;
};

#endif // ENTITY_HPP
