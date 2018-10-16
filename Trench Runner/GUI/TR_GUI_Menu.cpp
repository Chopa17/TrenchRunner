///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_GUI_Menu.cpp by Sam Brind																	 //
//		- The collection of GUI buttons that make up a menu										 //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "GUI/TR_GUI_Menu.h"

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"

#include <vector>

#include "Core/TR_GameManager.h"
#include "GUI/TR_GUI_Button.h"
#include "Utilities/TR_FileManager.h"

TR_GUI_Menu::TR_GUI_Menu()
	: m_bIsOpen{ false }
	, m_xRect{ sf::IntRect(0,0,0,0) }
	, m_xBackgroundTexture{}
	, m_xButtons{}
{
}

void TR_GUI_Menu::OpenMenu(const sf::IntRect& xRect, const char* szBackgroundTexture)
{
	m_xRect = xRect;
	SetBackgroundTexture(szBackgroundTexture);
	m_bIsOpen = true;
}

void TR_GUI_Menu::CloseMenu()
{
	m_xButtons.clear();
	m_xRect = sf::IntRect(0, 0, 0, 0);
	m_xBackgroundTexture = sf::Texture();
	m_bIsOpen = false;
}

void TR_GUI_Menu::HandleInput()
{
	if (!m_bIsOpen) return;

	sf::Event xEvent;
	while (TR_GameManager::GetGameWindow().pollEvent(xEvent))
	{
		if (xEvent.type == sf::Event::MouseButtonPressed)
		{
			for (auto xIt{ m_xButtons.begin() }; xIt != m_xButtons.end(); xIt++)
			{
				if ((*xIt).HandleInput(xEvent)) break;
			}
		}
	}
}

void TR_GUI_Menu::Draw()
{
	if (!m_bIsOpen) return;

	//draw background if needed
	if (m_xBackgroundTexture.getSize().x > 0 && m_xBackgroundTexture.getSize().y > 0)
	{
		//TODO : this is currently replicated alot, can it be moved to a manager function?
		sf::Sprite xSprite(m_xBackgroundTexture);
		float fScaleX = m_xRect.width / xSprite.getGlobalBounds().width;
		float fScaleY = m_xRect.height / xSprite.getGlobalBounds().height;
		xSprite.setScale(fScaleX, fScaleY);
		xSprite.setPosition(static_cast<float>(m_xRect.left), static_cast<float>(m_xRect.top));
		TR_GameManager::GetGameWindow().draw(xSprite);
	}

	//draw the buttons
	for (auto xIt{ m_xButtons.begin() }; xIt != m_xButtons.end(); xIt++)
	{
		(*xIt).Draw();
	}
}

void TR_GUI_Menu::AddButton(const TR_GUI_Button& xButton)
{
	//TODO : should this be set relative to the menu position?
	m_xButtons.push_back(xButton);
}

void TR_GUI_Menu::SetBackgroundTexture(const char* szTexture)
{
	TR_FileManager::LoadTextureFile(m_xBackgroundTexture, szTexture);
}
