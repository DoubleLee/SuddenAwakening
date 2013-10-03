#include "StateMainMenu.h"

#include "Game.h"
#include "AudioEffects.h"
#include "StringUtilities.h"
#include "Button.h"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "tinyxml2.h"
using namespace tinyxml2;

#include <stdexcept>

sf::Color gSelected( 50, 50, 255 );
sf::Color gNotSelected( 255, 255, 255 );

// StateMainMenu
StateMainMenu::StateMainMenu()
	:
	State( StateID::MainMenuID ),
	mSelectedButton(0)
	{
	string file("../Resources/Scripts/StateMainMenu.xml");
	LoadFromXML( ToPlatformPath(file) );
	ChangeSelectionTo(mSelectedButton);
	}

StateMainMenu::~StateMainMenu()
	{

	}

void StateMainMenu::Update()
	{
	TimeInt now ( mpGame->GetFrameStamp() );

	// Detect keyboard's space button down for shooting
	static TimeInt gunTrigger = 0;
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gunTrigger < now)
		{
		mpAudioEffects->PlaySound( AudioID::BasicLaserID );
		gunTrigger = now + 1000000;
		}

	mpAudioEffects->Update();
	}

void StateMainMenu::Draw()
	{
	sf::RenderWindow * const pWindow = mpGame->GetWindow();
	pWindow->draw( *mpBackground );

	for ( unique_ptr<Button> & pIndex : mButtons )
		{
		pIndex->Draw( (*pWindow) );
		}
	}

void StateMainMenu::ProcessEvent(const sf::Event & event)
	{
	TimeInt now( mpGame->GetFrameStamp() );

	// Detect click event and handle it
	if ( event.type == sf::Event::MouseButtonPressed )
		{
		//const sf::Event::MouseButtonEvent & mouseEvent = event;
		if (event.mouseButton.button == sf::Mouse::Left)
			{
			static TimeInt clickTrigger = 0;
			if ( clickTrigger < now )
				{
				mpAudioEffects->PlaySound( AudioID::ClickID );
				clickTrigger = now + (1000000 / 4);

				int i = 0;
				for ( unique_ptr<Button> & pIndex : mButtons )
					{
					Button * pButton( pIndex.get() );
					if ( pButton->Contains( event.mouseButton.x, event.mouseButton.y ) )
						{
						ChangeSelectionTo(i);
						UserMadeSelection();
						return;
						}
					++i;
					}
				}
			}
		}

	if ( event.type == sf::Event::KeyPressed )
		{
		if ( event.key.code == sf::Keyboard::Up )
			{
			ChangeSelectionBy(-1);
			}
		if ( event.key.code == sf::Keyboard::Down )
			{
			ChangeSelectionBy(1);
			}

		if ( event.key.code == sf::Keyboard::Return )
			{
			UserMadeSelection();
			}

		if ( event.key.code == sf::Keyboard::Escape )
			{
			mpGame->GetWindow()->close();
			}
		}
	}

void StateMainMenu::LoadFromXML(const string & file)
	{
	// Load the document
	XMLDocument doc;
	if ( doc.LoadFile( file.c_str() ) )
		{
		throw std::runtime_error("Failed to load and/or parse " + file);
		}

	LoadMusicFromXML( doc.FirstChildElement("music") );

	LoadTexturesFromXML( doc.FirstChildElement("textures") );

	LoadAudiosFromXML( doc.FirstChildElement("audios") );

	// Sprites code, this code can change quite a bit
	XMLElement * pSprites = doc.FirstChildElement("sprites");
	if ( ! pSprites )
		throw std::runtime_error("Failed to load sprites node");

	XMLElement * pBackground = pSprites->FirstChildElement("background");
	int index = -1;
	if ( pBackground->QueryIntAttribute("texIndex", &index) )
		throw std::runtime_error("Failed to find texIndex in background element");

	XMLElement * pButtons ( doc.FirstChildElement("buttons") );
	if ( !pButtons )
		{
		throw std::runtime_error("Failed to find buttons element");
		}

	XMLElement * pButton ( pButtons->FirstChildElement("button") );

	string buttonText;
	int textureIndex;
	sf::Vector2f pos;
	while ( pButtons && pButton )
		{
		const char * pStr( pButton->Attribute("text") );
		if ( !pStr )
			{
			throw std::runtime_error("Failed to find text attribute for button.");
			}

		buttonText = pStr;

		if ( pButton->QueryIntAttribute("texIndex", &textureIndex) )
			{
			throw std::runtime_error("Failed to find texIndex attribute for button.");
			}

		if ( pButton->QueryFloatAttribute("posx", &pos.x) )
			{
			throw std::runtime_error("Failed to find posX attribute for button.");
			}

		if ( pButton->QueryFloatAttribute("posy", &pos.y) )
			{
			throw std::runtime_error("Failed to find posY attribute for button.");
			}

		mButtons.emplace_back( new Button( mTextures.at(textureIndex), pos, ToPlatformPath(buttonText), 1 ) );
		pButton = pButton->NextSiblingElement("button");
		}


	mpBackground.reset( new sf::Sprite( mTextures.at(index) ) );
	}

void StateMainMenu::ChangeSelectionTo(int newSelection)
	{
	if ( newSelection < 0 )
		newSelection = 0;

	if ( newSelection > int(mButtons.size()) - 1 )
		newSelection = mButtons.size() - 1;

	if ( mButtons.empty() )
		return;
	// change old selected button back to not selected
	Button * pOldSelected ( mButtons.at(mSelectedButton).get() );
	Button * pNewSelected( mButtons.at(newSelection).get() );

	if ( !pOldSelected || !pNewSelected )
		return;

	pOldSelected->SetTextColor(gNotSelected);
	pNewSelected->SetTextColor(gSelected);
	mSelectedButton = newSelection;
	}

void StateMainMenu::ChangeSelectionBy( int offset )
	{
	int newIndex = (mSelectedButton + offset);

	ChangeSelectionTo(newIndex);
	}

void StateMainMenu::UserMadeSelection()
	{
	switch (mSelectedButton)
		{
		case 0: // New Game
			{
			mpGame->SetChangeToState( StateID::GamePlayID );
			break;
			}
		case 1: // Options
			{
			// TODO: write change to options state
			break;
			}
		case 2:
			{
			mpGame->GetWindow()->close();
			}
		}
	}
