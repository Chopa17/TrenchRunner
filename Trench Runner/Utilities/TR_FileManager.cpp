///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_FileManager.cpp by Sam Brind																 //
//		- Handles the opening of game files														 //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Utilities/TR_FileManager.h"

#include <string.h>

#include "SFML/Graphics/Texture.hpp"

const int TR_FileManager::iMAX_FILEPATH_LENGTH{ 50 };
const char* TR_FileManager::szGRAPHICS_FILEPATH{ "Resources/Art/" };
const char* TR_FileManager::szGRAPHICS_FILETYPE{ ".png" };

bool TR_FileManager::LoadTextureFile(sf::Texture& xTexture, const char* szFileName)
{
	if (!szFileName) return false;

	char szFilePath[iMAX_FILEPATH_LENGTH]{ '\0' };
	strcat_s(szFilePath, iMAX_FILEPATH_LENGTH, szGRAPHICS_FILEPATH);
	strcat_s(szFilePath, iMAX_FILEPATH_LENGTH, szFileName);
	strcat_s(szFilePath, iMAX_FILEPATH_LENGTH, szGRAPHICS_FILETYPE);

	return xTexture.loadFromFile(szFilePath);
}

