///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GUI_Menu.h by Sam Brind															         //
//		- The collection of GUI buttons that make up a menu										 //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TR_GUI_MENU_H
#define TR_GUI_MENU_H

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <vector>

#include "GUI/TR_GUI_Button.h"

class TR_GUI_Menu
{
public:
	TR_GUI_Menu();
	
	void OpenMenu(const sf::IntRect& xRect, const char* szTexture = nullptr);
	void CloseMenu();
	inline bool IsOpen() const { return m_bIsOpen; }

	void HandleInput();
	void Draw();

	//TODO : Might become a more general AddItem(GUI_BaseClass*)?
	void AddButton(const TR_GUI_Button& xButton);
	void SetBackgroundTexture(const char* szTexture);

private:
	bool m_bIsOpen;
	sf::IntRect m_xRect;
	sf::Texture m_xBackgroundTexture;
	std::vector<TR_GUI_Button> m_xButtons;
	//TODO : an escape/back callback?
};

#endif

