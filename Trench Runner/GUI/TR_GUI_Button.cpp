///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GUI_Button.cpp by Sam Brind																 //
//		- A button for GUI buttons																 //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "GUI/TR_GUI_Button.h"

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"

#include "Core/TR_GameManager.h"
#include "Utilities/TR_FileManager.h"

TR_GUI_Button::TR_GUI_Button(const sf::IntRect& xRect, const char* szDefaultTexture)
	: m_bIsVisible{ false }
	, m_fnOnClick{ nullptr }
	, m_xRect{ xRect }
	, m_xDefaultTexture{}
	, m_xHoverTexture{}
{
	SetDefaultTexture(szDefaultTexture);
	Show();
}

bool TR_GUI_Button::HandleInput(const sf::Event& xEvent)
{
	if (!m_bIsVisible) return false;

	if (xEvent.type == sf::Event::MouseButtonPressed)
	{
		if (m_fnOnClick && m_xRect.contains( TR_GameManager::GetMousePos() ))
		{
			m_fnOnClick();
			return true;
		}
	}
	return false;
}

void TR_GUI_Button::Draw()
{
	if (!m_bIsVisible) return;

	sf::Sprite xButton;

	if (m_xRect.contains( TR_GameManager::GetMousePos() ))
	{
		xButton.setTexture(m_xHoverTexture);
	}
	else
	{
		xButton.setTexture(m_xDefaultTexture);
	}
	float fScaleX = m_xRect.width / xButton.getGlobalBounds().width;
	float fScaleY = m_xRect.height / xButton.getGlobalBounds().height;
	xButton.setScale(fScaleX, fScaleY);
	xButton.setPosition(static_cast<float>(m_xRect.left), static_cast<float>(m_xRect.top));

	TR_GameManager::GetGameWindow().draw(xButton);
}

inline void TR_GUI_Button::Hide()
{
	m_bIsVisible = false;
}

void TR_GUI_Button::Show()
{
	if (m_xDefaultTexture.getSize().x > 0 && m_xDefaultTexture.getSize().y > 0)
	{
		m_bIsVisible = true;
	}
}

void TR_GUI_Button::SetClickCallback(void(*fnFunc)())
{
	if (fnFunc)
	{
		m_fnOnClick = fnFunc;
	}
}

void TR_GUI_Button::SetDefaultTexture(const char* szTexture)
{
	TR_FileManager::LoadTextureFile(m_xDefaultTexture, szTexture);
}

void TR_GUI_Button::SetHoverTexture(const char * szTexture)
{
	TR_FileManager::LoadTextureFile(m_xHoverTexture, szTexture);
}
