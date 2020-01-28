#pragma once

#include <FTGL\ftgl.h>
#include  "GameConstants.h"
#include "Font.h"

class FontManager    //The Font Manager Class
{

private:

	static FontManager* fInstance;	   //Instantiates the Font Manager
	map<LPCSTR, Font*> gameFonts;	   //Creates the Font Map

public:
	static FontManager* getInstance(); //Finds the Instance of the Font Mangager

	FontManager();					              //Class Constructor
	~FontManager();							      //Class Destructor.
	void AddFont(LPCSTR fontName, LPCSTR fileName, int fontSize);    //Adds the Font to the Game
	Font* getFont(LPCSTR fontName);				                  
	void DeleteFont();								                 //Deletes the Font from the Game
};
