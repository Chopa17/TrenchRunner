///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GameState.cpp by Sam Brind																 //
//		- The state of the game being played    					                             //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Core/TR_GameState.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"

#include "Core/TR_GameManager.h"

//TODO : remove this test texture with a real background
static sf::Texture xInGameTexture;

TR_GameState::TR_GameState()
{
}

void TR_GameState::Initialise()
{
	xInGameTexture.loadFromFile("Resources/Art/Test/Game.png");
	//TODO : Initialise the game objects
}

void TR_GameState::Cleanup()
{
	//TODO : Cleanup the game objects
}

void TR_GameState::HandleInput()
{
	sf::Event xEvent;
	while (TR_GameManager::GetGameWindow().pollEvent(xEvent))
	{
		if (xEvent.type == sf::Event::MouseButtonPressed)
		{
			TR_GameManager::RequestState(TR_GameManager::GameStates::PAUSE_MENU);
		}
		if (xEvent.type == sf::Event::KeyPressed)
		{
			TR_GameManager::RequestState(TR_GameManager::GameStates::GAME_OVER);
		}
	}
	//TODO : Handle real game input
}

void TR_GameState::Update()
{
	//TODO : Update the game logic
}

void TR_GameState::Draw()
{
	sf::Sprite xSprite(xInGameTexture);
	float fScaleX = TR_GameManager::GetWindowWidth() / xSprite.getGlobalBounds().width;
	float fScaleY = TR_GameManager::GetWindowHeight() / xSprite.getGlobalBounds().height;
	xSprite.setScale(fScaleX, fScaleY);
	xSprite.setPosition(0, 0);
	TR_GameManager::GetGameWindow().draw(xSprite);

	//TODO : Draw the game scene
}

