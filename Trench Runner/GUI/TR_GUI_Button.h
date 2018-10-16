///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GUI_Button.h by Sam Brind															         //
//		- A button for GUI interfaces															 //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TR_GUI_BUTTON_H
#define TR_GUI_BUTTON_H

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace sf
{
	class Event;
}

class TR_GUI_Button
{
	friend class TR_GUI_Menu;

public:
	TR_GUI_Button() = delete;
	explicit TR_GUI_Button(const sf::IntRect& xRect, const char* szDefaultTexture = nullptr);

	bool HandleInput(const sf::Event& xEvent);
	void Draw();

	inline void Hide();
	void Show();

	void SetClickCallback(void(*fnFunc)());
	void SetDefaultTexture(const char* szTexture);
	void SetHoverTexture(const char* szTexture);

private:
	bool m_bIsVisible;

	void(*m_fnOnClick)();
	
	sf::IntRect m_xRect;
	
	sf::Texture m_xDefaultTexture;
	sf::Texture m_xHoverTexture;
};

#endif
