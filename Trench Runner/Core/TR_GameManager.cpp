///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GameManager.cpp by Sam Brind																 //
//		- The manager of the games current state									             //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Core/TR_GameManager.h"

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"

#include <Windows.h>

#include "Core/TR_GameState.h"
#include "GUI/TR_GUI_Button.h"
#include "GUI/TR_GUI_Menu.h"

bool TR_GameManager::s_bIsGameRunning{ false };

unsigned int TR_GameManager::s_uWorldHeight{ 0 };
unsigned int TR_GameManager::s_uWorldWidth{ 0 };
float TR_GameManager::s_fScreenToWorldRatio_Height{ 1.0f };
float TR_GameManager::s_fScreenToWorldRatio_Width{ 1.0f };

TR_GameManager::GameStates TR_GameManager::s_eCurrentState{ GameStates::TITLE_SCREEN };
TR_GameState TR_GameManager::s_xGameState{};
TR_GUI_Menu TR_GameManager::s_xGameMenu{};

sf::RenderWindow TR_GameManager::s_xGameWindow{};

sf::Vector2i TR_GameManager::GetMousePos()
{
	//TODO : gets mouse pos in desktop (needs to handle game(x,y) -> desktop(x,y)?)
	const sf::Vector2i xPixelPos = sf::Mouse::getPosition( TR_GameManager::GetGameWindow() );
	const sf::Vector2f xWorldPos = TR_GameManager::GetGameWindow().mapPixelToCoords(xPixelPos);
	return static_cast<sf::Vector2i>(xWorldPos);
}

int TR_GameManager::GetWindowHeight()
{
	return static_cast<int>(GetGameWindow().getView().getSize().y);
}

int TR_GameManager::GetWindowWidth()
{
	return static_cast<int>(GetGameWindow().getView().getSize().x);
}

//game management
void TR_GameManager::StartGame()
{
	//TODO : Allow user to choose a different window size (from set of choices)
	//create the Game window
	s_xGameWindow.create(sf::VideoMode::getFullscreenModes()[0], "Trench Runner");
	::ShowWindow(s_xGameWindow.getSystemHandle(), SW_MAXIMIZE);
	s_xGameWindow.setFramerateLimit(60);
	s_xGameWindow.setVisible(true);
	s_xGameWindow.requestFocus();

	Initialise();
	s_bIsGameRunning = true;
}

void TR_GameManager::EndGame()
{
	Cleanup();

	s_bIsGameRunning = false;

	s_xGameWindow.close();
}

void TR_GameManager::ResumeGame()
{
	RequestState(GameStates::IN_GAME);
}

void TR_GameManager::RestartGame()
{
	s_xGameState.Initialise();
	RequestState(GameStates::IN_GAME);
}

void TR_GameManager::QuitMenu()
{
	//TODO : this may need to become more complex
	RequestState(GameStates::TITLE_SCREEN);
}

void TR_GameManager::RequestState(const GameStates eState)
{
	//TODO : Add assert for request that doesn't come from a valid state?
	switch (eState)
	{
		case GameStates::TITLE_SCREEN:
		{
			if (   s_eCurrentState == GameStates::IN_GAME 
				|| s_eCurrentState == GameStates::PAUSE_MENU
				|| s_eCurrentState == GameStates::GAME_OVER)
			{
				s_xGameMenu.CloseMenu();
				SetupTitleScreenMenu();

				s_eCurrentState = GameStates::TITLE_SCREEN;
			}
			break;
		}

		case GameStates::IN_GAME:
		{
			if (   s_eCurrentState == GameStates::TITLE_SCREEN
				|| s_eCurrentState == GameStates::PAUSE_MENU
				|| s_eCurrentState == GameStates::GAME_OVER)
			{
				s_xGameMenu.CloseMenu();
				s_eCurrentState = GameStates::IN_GAME;
			}
			break;
		}

		case GameStates::PAUSE_MENU:
		{
			if (s_eCurrentState == GameStates::IN_GAME)
			{
				SetupPauseScreenMenu();
				s_eCurrentState = GameStates::PAUSE_MENU;
			}
			break;
		}

		case GameStates::GAME_OVER:
		{
			if (s_eCurrentState == GameStates::IN_GAME)
			{
				SetupGameOverMenu();
				s_eCurrentState = GameStates::GAME_OVER;
			}
			break;
		}

		default:
		{
			//Error
			break;
		}
	}
}

void TR_GameManager::Initialise()
{
	//s_xGameState.Initialise();
	SetupTitleScreenMenu();
}

void TR_GameManager::Cleanup()
{
	s_xGameMenu.CloseMenu();
	s_xGameState.Cleanup();
}

void TR_GameManager::HandleInput()
{
	if (s_xGameMenu.IsOpen())
	{
		s_xGameMenu.HandleInput();
	}
	else
	{
		s_xGameState.HandleInput();
	}
}

void TR_GameManager::Update()
{
	//TODO : Dynamic menus?
	s_xGameState.Update();
}

void TR_GameManager::Draw()
{
	GetGameWindow().clear();

	s_xGameState.Draw();
	s_xGameMenu.Draw();

	GetGameWindow().display();
}

void TR_GameManager::SetupTitleScreenMenu()
{
	GetGameMenu().OpenMenu(sf::IntRect(0, 0, GetWindowWidth(), GetWindowHeight()), "Test/TitleMenu");

	TR_GUI_Button xStartGame(sf::IntRect(150, 150, 200, 100), "Test/StartButton");
	xStartGame.SetClickCallback(RestartGame);
	xStartGame.SetHoverTexture("Test/StartButton_hover");
	GetGameMenu().AddButton(xStartGame);

	TR_GUI_Button xCloseGame(sf::IntRect(150, 300, 200, 100), "Test/CloseButton");
	xCloseGame.SetClickCallback(EndGame);
	xCloseGame.SetHoverTexture("Test/CloseButton_hover");
	GetGameMenu().AddButton(xCloseGame);
}

void TR_GameManager::SetupPauseScreenMenu()
{
	GetGameMenu().OpenMenu(sf::IntRect(100, 100, 300, 500), "Test/PauseMenu");

	TR_GUI_Button xResumeGame(sf::IntRect(150, 150, 200, 100), "Test/ResumeButton");
	xResumeGame.SetClickCallback(ResumeGame);
	xResumeGame.SetHoverTexture("Test/ResumeButton_hover");
	GetGameMenu().AddButton(xResumeGame);

	TR_GUI_Button xRestartGame(sf::IntRect(150, 300, 200, 100), "Test/RestartButton");
	xRestartGame.SetClickCallback(RestartGame);
	xRestartGame.SetHoverTexture("Test/RestartButton_hover");
	GetGameMenu().AddButton(xRestartGame);

	TR_GUI_Button xQuitGame(sf::IntRect(150, 450, 200, 100), "Test/QuitButton");
	xQuitGame.SetClickCallback(QuitMenu);
	xQuitGame.SetHoverTexture("Test/QuitButton_hover");
	GetGameMenu().AddButton(xQuitGame);
}

void TR_GameManager::SetupGameOverMenu()
{
	GetGameMenu().OpenMenu(sf::IntRect(100, 100, 300, 350), "Test/GameOverMenu");

	TR_GUI_Button xRestartGame(sf::IntRect(150, 150, 200, 100), "Test/RestartButton");
	xRestartGame.SetClickCallback(RestartGame);
	xRestartGame.SetHoverTexture("Test/RestartButton_hover");
	GetGameMenu().AddButton(xRestartGame);

	TR_GUI_Button xQuitGame(sf::IntRect(150, 300, 200, 100), "Test/QuitButton");
	xQuitGame.SetClickCallback(QuitMenu);
	xQuitGame.SetHoverTexture("Test/QuitButton_hover");
	GetGameMenu().AddButton(xQuitGame);
}
