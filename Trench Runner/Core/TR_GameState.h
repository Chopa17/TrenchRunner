///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GameState.h by Sam Brind																     //
//		- The game state definition									                             //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TR_GAME_STATE_H
#define TR_GAME_STATE_H

class TR_GameState
{
public:
	TR_GameState();

	void Initialise();
	void Cleanup();

	void HandleInput();
	void Update();
	void Draw();
};

#endif
