///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_InputHandler.h by Sam Brind															     //
//		- Contains the control mappings	and checks for inputs									 //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TR_INPUT_HANDLER_H
#define TR_INPUT_HANDLER_H

class TR_InputHandler
{
public:
	enum class ControlInput : unsigned char
	{
		//Game flow
		CLOSE_GAME,
		NEW_GAME,
		QUIT_GAME,
		RESTART_GAME, //TODO : could share with NEW_GAME?

		//Gameplay
		JUMP
		//TODO : gameplay...
	};

	static bool CheckInput(const ControlInput eControl);
};

#endif
