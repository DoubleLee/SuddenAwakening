#ifndef BUTTON_H
#define BUTTON_H

#include <memory>
#include <string>
using std::unique_ptr;
using std::string;

#include "SFML/Graphics.hpp"

class Button
{
public:
	Button( sf::Texture & texture, const sf::Vector2f & pos, string & text, int buttonID);

	bool IsPosWithin( const sf::Vector2f & pos );

	void Draw( sf::RenderWindow & renderWindow );

	void SetTextColor( const sf::Color & color );

	int GetButtonID() const;

	bool Contains( float x, float y );

private:
	sf::Sprite mSprite;
	int mButtonID;
	sf::Text mText;
};

#endif // BUTTON_H
