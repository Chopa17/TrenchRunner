///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GameManager.h by Sam Brind																 //
//		- The manager of the games current state									             //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TR_GAME_MANAGER_H
#define TR_GAME_MANAGER_H

#include "SFML/Graphics/RenderWindow.hpp"

#include "Core/TR_GameState.h"
#include "GUI/TR_GUI_Menu.h"

class TR_GameManager
{
public:
	//game management
	enum class GameStates : unsigned char
	{
		TITLE_SCREEN,
		IN_GAME,
		PAUSE_MENU,
		GAME_OVER,
		INVALID_STATE
	};

	static void Initialise();
	static void Cleanup();

	static void HandleInput();
	static void Update();
	static void Draw();

	static void RequestState(const GameStates eState);
	
	static void StartGame();
	static void EndGame();
	static void ResumeGame();
	static void RestartGame();
	static void QuitMenu();
	inline static bool IsGameRunning() { return s_bIsGameRunning; }

	inline static sf::RenderWindow& GetGameWindow() { return s_xGameWindow; }
	inline static TR_GUI_Menu& GetGameMenu() { return s_xGameMenu; }

	static sf::Vector2i GetMousePos();
	static int GetWindowHeight();
	static int GetWindowWidth();

private:
	TR_GameManager() {}

	static bool s_bIsGameRunning;

	static void SetupTitleScreenMenu();
	static void SetupPauseScreenMenu();
	static void SetupGameOverMenu();

	static unsigned int s_uWorldHeight;
	static unsigned int s_uWorldWidth;
	static float s_fScreenToWorldRatio_Height;
	static float s_fScreenToWorldRatio_Width;

	//TODO : Eurgh
	static GameStates s_eCurrentState;
	static TR_GameState s_xGameState;
	static TR_GUI_Menu s_xGameMenu;

	static sf::RenderWindow s_xGameWindow;
};

#endif
