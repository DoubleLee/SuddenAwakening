#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <memory>
#include <string>
using std::unique_ptr;
using std::string;

#include "SFML/Graphics.hpp"

// TODO: make the Button class take in a Font &

/**
 * @brief The Button class.
 * This class represents a clickable and selectable button.
 *
 * I wrote this instead of using a GUI library.
 *
 * Pass it a loaded texture for the button background, a position for the buttons top left corner,
 * the text to display on the button, and an ID which you can associate with the button.
 */
class Button
{
public:
	/**
	 * @brief Button ctor, builds a button that may be clicked, use IsPosWithin to detect clicks.
	 * @param texture The texture for the button background.
	 * @param pos The position of the top left corner.
	 * @param text The text to display centered on the button.
	 * @param buttonID The optional button ID you may associate with this button.
	 */
	Button( sf::Texture & texture, const sf::Vector2f & pos, string & text, int buttonID = 0);

	/**
	 * @brief Draw will use sfml2 to draw to the window the button, including the texture and text.
	 * @param renderWindow The window to render to.
	 */
	void Draw( sf::RenderWindow & renderWindow );

	/**
	 * @brief SetTextColor sets the text color to whatever you like.
	 * @param color The color to set the text.
	 */
	void SetTextColor( const sf::Color & color );

	/**
	 * @brief GetButtonID getter for the button ID you chose to associate with this button.
	 *
	 * @return The associated button ID.
	 */
	int GetButtonID() const;

	/**
	 * @brief IsPosWithin checks if the given 2d cordinate is within the button bounds.
	 * Usefull for detecting button clicks.
	 * @param pos The position to check.
	 * @return Yes or no if the position is inside.
	 */
	bool IsPosWithin( const sf::Vector2f & pos );

	/**
	 * @brief IsPosWithin IsPosWithin checks if the given 2d cordinate is within the button bounds.
	 * Usefull for detecting button clicks.
	 * @param x The x coordinate to check.
	 * @param y The y coordinate to check.
	 * @return Yes or no if the position is inside.
	 */
	bool IsPosWithin( float x, float y );

private:
	sf::Sprite mSprite;
	int mButtonID;
	sf::Text mText;
};

#endif // BUTTON_H
