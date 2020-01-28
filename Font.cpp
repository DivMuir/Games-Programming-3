
#pragma warning ( disable : 4996 )

#include "Font.h"

Font::Font() //Class Constructor
{
	TheFont = NULL;   // The Font Variable is Cleared
}


Font::Font(LPCSTR fontFileName, int fontSize)	//Constructor that takes in the Font Name and Size
{
	TheFont = new FTTextureFont(fontFileName);    //Font is loaded from file 

	if (TheFont == NULL)                                                                                          //If a font hasn't been loaded
	{
		MessageBox(NULL, "Failure to Create Font", "An error occurred", MB_ICONERROR | MB_OK);       //Display Error Message
		delete TheFont;
	}

	if (!TheFont->FaceSize(fontSize));                                                                            //If the Font Size can't/Hasn't be set
	{
		MessageBox(NULL, "Unable to set desired size for Font!", "An error occurred", MB_ICONERROR | MB_OK);      //Display Error Message
		delete TheFont;
	}
}

Font::~Font()	          //Class Destructor
{
	delete TheFont;       //Deletes the Font
}

FTFont* Font::getFont()    //Finds the Font
{
	return TheFont;
}

void Font::PrintText(LPCSTR text, FTPoint textPos)      //Renders the Text to the screen
{
	glPushMatrix();
	glTranslatef(textPos.X(), textPos.Y(), 0);        //Sets the Text's position
	glScalef(1, -1, 1);                               //Sets the Text's Scale
	glColor3f(0.0f, 255.0f, 0.0f);                    //Sets the Text's Colour to Green
	TheFont->Render(text);                            //Renders the Text to the Screen

	glPopMatrix();
}

void Font::PrintText(LPCSTR text, FTPoint textPos, colour3f textColour)
{
	glPushMatrix();
	glTranslatef(textPos.X(), textPos.Y(), 0);                   //Sets the Text's Position
	glScalef(1, -1, 1);                                          //Sets the Text's Scale
	glColor3f(textColour.r, textColour.g, textColour.b);         //Sets the Text to the Desired Colour
	TheFont->Render(text);                                       //Renders the Text to the Screen
	glPopMatrix();
}