#pragma once
#include "GameConstants.h"   //Links the Game Contstants

class GameDisplay     //Game Display Class
{
private:
	SDL_Window* GameWindow;	     //Sets Up the Game Window
	SDL_GLContext GLContext;	 //Sets Up the OpenGL Context
	bool WindowClosed;	         //Boolean for checking if the Game window is open

public:
	GameDisplay() {}	//Class Constructor
	GameDisplay(int WindowWidth, int WindowHeight, const std::string& WindowName);	//Class Constructor that takes  in the Window Sizes and the Window Name
	~GameDisplay();	                                                                //Class Destructor

	void ClearDisplayColour(float r, float g, float b, float a);	  //Clears the Display Screen
	void SwapBuffers();                                               //Swaps the Buffer to the Screen 
	bool IsClosed();	                                              //Checks if the Game Window is closed

	void SetOrthographicProj(int Width, int Height);	//Sets the Orthographic Projection for the Display
	void Resize(int Width, int Height);	                //Resizes the Game Display
	void SetMVP(int Width, int Height);	                //Sets the Model View
};