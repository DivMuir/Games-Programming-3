#pragma once

#ifndef _Font_H
#define _Font_H

#include "GameConstants.h"
#include <FTGL\ftgl.h>

class Font   //The Font Class
{
private:
	FTFont* TheFont;	//Creates the Font Object

public:
	Font();	                                    //Class Constructor
	Font(LPCSTR fontFileName, int fontSize);    //Class Constructor with File Name and Font intake 
	~Font();                                    //Destructor
	FTFont* getFont();                          //Finds the Font

	void PrintText(LPCSTR text, FTPoint textPos);                        //Method to Print text to the Screen
	void PrintText(LPCSTR text, FTPoint textPos, colour3f textColour);   //Method to Print text to the Screen in a certain Colour

};
#endif