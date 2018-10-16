///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GameCore.cpp by Sam Brind																     //
//		- Contains the core game loop									                         //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SFML/System/Clock.hpp"

#include "Core/TR_GameManager.h"

//TODO : Move stuff like this into a TR_GameCore.h?
#include <iostream>
static const int iTR_FRAMES_PER_SECOND{ 60 };
static const sf::Time xTR_MICROSECS_PER_FRAME{ sf::microseconds(1000000 / iTR_FRAMES_PER_SECOND) };
static const int iTR_MAX_UPDATES{ 5 };

int main()
{
	TR_GameManager::StartGame();

	//TODO : Do we need a better loop than fixed timestep?
	//TODO : Do we need to move the clock into another class?
	sf::Clock xGameClock;
	xGameClock.restart();
	sf::Time xElapsedTime{ sf::microseconds(0) };

	while (TR_GameManager::IsGameRunning())
	{
		xElapsedTime += xGameClock.restart();

		//DEBUG : view frame time
		//int iStart = xGameClock.getElapsedTime().asMilliseconds();

		int iUpdateCount{ 0 };
		while(xElapsedTime >= xTR_MICROSECS_PER_FRAME && iUpdateCount < iTR_MAX_UPDATES)
		{
			xElapsedTime -= xTR_MICROSECS_PER_FRAME;
			TR_GameManager::HandleInput();
			TR_GameManager::Update();
			iUpdateCount++;
		}
		TR_GameManager::Draw();

		//DEBUG : view frame time
		//std::cout << "Time per frame : " << xGameClock.getElapsedTime().asMilliseconds() - iStart << "ms" << std::endl;
	}

	//If console log needs to be checked after closing the game
	//getchar();

	return 0;
}