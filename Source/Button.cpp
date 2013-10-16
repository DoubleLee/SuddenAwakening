#include "Button.hpp"

#include "Game.hpp"

Button::Button( sf::Texture & texture, const sf::Vector2f & pos, string & text, int buttonID)
	:
	mSprite(texture),
	mButtonID(buttonID),
	mText( text, Game::Get()->GetButtonFont() )
	{
	mText.setPosition( pos );// + sf::Vector2f(5.0f, 0.0f) );
	mSprite.setPosition( pos );
	sf::FloatRect textRect (mText.getGlobalBounds() );
	sf::FloatRect spriteRect( mSprite.getGlobalBounds() );

	sf::FloatRect newRect(textRect);
	newRect.height += (textRect.height / 2.0f);
	newRect.width += (textRect.height / 2.0f);

	mText.setPosition( pos + sf::Vector2f((newRect.width - textRect.width) / 2.0f, 0.0f) );

	float x = newRect.width / spriteRect.width;
	float y = newRect.height / spriteRect.height;
	mSprite.setScale( x, y );
	}

bool Button::IsPosWithin(const sf::Vector2f & pos)
	{
	sf::FloatRect rect = mSprite.getGlobalBounds();

	return rect.contains( sf::Vector2f(pos) );
	}

void Button::Draw(sf::RenderWindow & renderWindow)
	{
	renderWindow.draw(mSprite);
	renderWindow.draw(mText);
	}

void Button::SetTextColor(const sf::Color &color)
	{
	mText.setColor(color);
	}

int Button::GetButtonID() const
	{
	return mButtonID;
	}

bool Button::Contains(float x, float y)
	{
	return mSprite.getGlobalBounds().contains( x, y );
	}
