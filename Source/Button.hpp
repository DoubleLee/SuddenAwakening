#pragma once

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

	// draw button to window
	void Draw( sf::RenderWindow & renderWindow );

	// sets the color of the text on the button
	void SetTextColor( const sf::Color & color );

	// return the button id field
	int GetButtonID() const;

	// check if point is within the button bounds
	bool IsPosWithin( const sf::Vector2f & pos );
	bool IsPosWithin( float x, float y );

private:
	sf::Sprite mSprite;
	int mButtonID;
	sf::Text mText;
};

#endif // BUTTON_H
