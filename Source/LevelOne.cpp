#include "LevelOne.hpp"

#include "Game.hpp"
#include "StringUtilities.hpp"
#include "XMLFunctions.hpp"
#include "Entity.hpp"
#include "TileMap.hpp"

#include "tinyxml2.hpp"
using namespace tinyxml2;

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

LevelOne::LevelOne()
	:
	Level( LevelID::LevelOne )
	{
	string file("../Resources/Scripts/LevelOne.xml");
	LoadFromXML( ToPlatformPath(file) );
	}

LevelOne::~LevelOne()
	{

	}

void LevelOne::Update()
	{
	UpdatePlayer();
	}

void LevelOne::UpdatePlayer()
	{
	Game * pGame = Game::Get();
	TimeInt now = pGame->GetFrameStampInt();
	float frameDelta = static_cast<float>(pGame->GetFrameDeltaD());
	int mapTileSize = pGame->GetMapTileSize();

	Player * pPlayer = mpPlayer.get();

	if ( pPlayer == nullptr )
		return;

	sf::Vector2f oldPos = pPlayer->GetPosition();

	sf::Vector2f moveVec(0.0f,0.0f);
	float tileMultiplier = 3.0f;
	float speed = mapTileSize * tileMultiplier * frameDelta;

	int yCoord = pPlayer->GetYCoord();
	int xCoord = pPlayer->GetXCoord();

	int xDirection = pPlayer->GetXDirection();

	int textureSheetWidth = pPlayer->GetTextureSheetWidth();
	int textureSheetHeight = pPlayer->GetTextureSheetHeight();

	TimeInt nextFrameTrigger = pPlayer->GetNextFrameTrigger();


	// set animation direction on Y cordinate of sheet
	bool directionPressed = false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
		{
		yCoord = static_cast<int>( Direction::Right );
		moveVec.x += speed;
		directionPressed = true;
		}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
		{
		yCoord = static_cast<int>( Direction::Left );
		moveVec.x -= speed;
		directionPressed = true;
		}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
		{
		yCoord = static_cast<int>( Direction::Up );
		moveVec.y -= speed;
		directionPressed = true;
		}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
		{
		yCoord = static_cast<int>( Direction::Down );
		moveVec.y += speed;
		directionPressed = true;
		}

	// move animation forward each time step
	if ( nextFrameTrigger <= now )
		{
		// if a direction is pressed move the animation forward
		if ( directionPressed )
			{
			xCoord += xDirection;
			// check high side
			if ( xCoord > (textureSheetWidth - 1) )
				{
				xDirection = -1;
				xCoord = (textureSheetWidth - 1) - 1;
				}
			// check low side
			if ( xCoord < 0 )
				{
				xDirection = 1;
				xCoord = 1;
				}
			}
		else  // if no button is pressed change to first frame for standing
			{
			xDirection = 1;
			xCoord = 0;
			}

		// move the trigger forward
		nextFrameTrigger = now + TimeInt(132000);
		pPlayer->SetNextFrameTrigger(nextFrameTrigger);
		}

	pPlayer->SetXCoord(xCoord);
	pPlayer->SetYCoord(yCoord);
	pPlayer->SetXDirection(xDirection);

	// calculate and set texture rect
	sf::IntRect rect;
	rect.top = yCoord * mapTileSize;
	rect.left = xCoord * mapTileSize;

	rect.height = mapTileSize;
	rect.width = mapTileSize;

	sf::Sprite * pSprite = pPlayer->GetSprite();
	pSprite->setTextureRect( rect );
	// move sprite according to the value calculated
	pSprite->move( moveVec );

	TileMap * pTileMap = mpTileMap.get();

	if ( !pTileMap->IsValidPosition( pSprite ) )
		{
		pSprite->setPosition(oldPos);
		}
	}

void LevelOne::Draw()
	{
	sf::RenderWindow * pWindow( mpGame->GetWindow() );

	if ( mpTileMap )
		mpTileMap->Draw(pWindow);

	if ( mpPlayer )
		mpPlayer->Draw(pWindow);
	}

void LevelOne::LoadFromXML(const string & file)
	{
	XMLDocument doc;
	if ( doc.LoadFile( file.c_str() ) )
		{
		ThrowRuntimeException("Failed to load xml file, " + file )
		}

	LoadTexturesFromXML( mTextures, doc.FirstChildElement("textures") );

	LoadMusicFromXML( *(mpGame->GetMusic()), doc.FirstChildElement("music") );

	string mapFile;
	XMLElement * pMap( doc.FirstChildElement("map") );

	const char * pMapFile = pMap->Attribute("file");
	if ( !pMapFile )
		{
		ThrowRuntimeException("Failed to find map element in Level xml")
		}

	mapFile = pMapFile;

	ToPlatformPath(mapFile);

	mpTileMap.reset( new TileMap( mapFile ) );

	// player load
	XMLElement * pPlayerElement = doc.FirstChildElement("player");

	if ( !pPlayerElement )
		{
		ThrowRuntimeException("Failed to find player node in level xml")
		}

	int playerTexID = -1;

	if ( pPlayerElement->QueryIntAttribute("texID", &playerTexID) )
		ThrowRuntimeException("Failed to find player texID in level xml")

	mpPlayer.reset( new Player( mTextures.GetResource(playerTexID), mpTileMap->GetSpawnPosition() ) );
	}

void LevelOne::ProcessEvent(const sf::Event & event)
	{

	}
