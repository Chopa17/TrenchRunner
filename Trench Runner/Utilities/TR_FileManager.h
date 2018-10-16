///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_FileManager.h by Sam Brind															     //
//		- Handles the opening of game files														 //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TR_FILE_MANAGER_H
#define TR_FILE_MANAGER_H

namespace sf
{
	class Texture;
}

class TR_FileManager
{
public:
	//TODO : does it need to be templated?
	//template <typename T>
	//static bool LoadFile(T& xTarget, const char* szFilePath, const char* szFileName, const char* szFileType);

	static bool LoadTextureFile(sf::Texture& xTexture, const char* szFileName);
	//static bool LoadAudioFile(sf::Sound& xSound, const char* szFilename);

private:
	static const int iMAX_FILEPATH_LENGTH;
	static const char* szGRAPHICS_FILEPATH;
	static const char* szGRAPHICS_FILETYPE;
};

#endif
