
#include "FontManager.h"

FontManager* FontManager::fInstance = NULL;

FontManager* FontManager::getInstance()     //Finds the Font Managers Instance
{
	if (fInstance == NULL)                //If the Instance doesn't exist
	{ 
		fInstance = new FontManager();    //Create a new Instance
	}
	return FontManager::fInstance;        //Return the Instance
}

FontManager::FontManager() //Class Constructor
{
}

FontManager::~FontManager()	//Destructor						
{
	DeleteFont();           //Deletes the Font
}


void FontManager::AddFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  //Adds the Font to the game
{
	if (!getFont(fontName))                                    
	{
		Font * newFont = new Font(fileName, fontSize);
		gameFonts.insert(make_pair(fontName, newFont));
	}
}

Font* FontManager::getFont(LPCSTR fontName)	                                    //Finds the Font 
{
	map<LPCSTR, Font*>::iterator TheFont = gameFonts.find(fontName);
	if (TheFont != gameFonts.end())
	{
		return TheFont->second;
	}
	else
	{
		return NULL;
	}
}
void FontManager::DeleteFont()		//Deletes the Font
{
	for (map<LPCSTR, Font*>::const_iterator TheFont = gameFonts.begin(); TheFont != gameFonts.end(); TheFont++)
	{
		delete TheFont->second;
	}
}