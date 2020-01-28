#include "GameDisplay.h"
#include <GL\glew.h>
#include <iostream>

GameDisplay::GameDisplay(int WindowWidth, int WindowHeight, const std::string& WindowName)
{
	SDL_Init(SDL_INIT_EVERYTHING);                      //Initialises SDL

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);             //
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);           //
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);            //
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);           //Sets attributes to help with displaying colours etc
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);         //
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);          //
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);         //

	GameWindow = SDL_CreateWindow(WindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_OPENGL);    //Creates the Game Window
	GLContext = SDL_GL_CreateContext(GameWindow);                                                                                                       //Binds the Game Window to the Context

	GLenum status = glewInit();     //Initialises Glew
	if (status != GLEW_OK)                                       //If Glew Doesn't Initialise properly 
	{
		std::cerr << "Glew failed to initialise" << std::endl;   //Display Error Message
	}

	WindowClosed = false;     //Sets the Window as Closed

	
	glEnable(GL_DEPTH_TEST);   //Enables depth testing
	glEnable(GL_CULL_FACE);    //Enables face culling 
	glCullFace(GL_BACK);
}

GameDisplay::~GameDisplay()        //Class Deconstructor
{
	SDL_GL_DeleteContext(GLContext);    //Deletes the Game Window Context
	SDL_DestroyWindow(GameWindow);      //Destroys the Game Window
	SDL_Quit();                         //Quits SDL closing the Window
}

void GameDisplay::ClearDisplayColour(float r, float g, float b, float a)        //Clears the Display 
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool GameDisplay::IsClosed()             //Method that Checks if the Game Diplay has been closed
{
	return WindowClosed;
}

void GameDisplay::SetOrthographicProj(int width, int height)     //Sets the Orthographic projection for the Window 
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, 0.0, -1.0);
}

void GameDisplay::SetMVP(int width, int height)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glClearStencil(0);                          
	glClearDepth(1.0f);                         
	glDepthFunc(GL_LEQUAL);
	Resize(width, height);
}

void GameDisplay::Resize(int width, int height)          //Method For Resizing the Game Window
{
	glViewport(0, 0, width, height);           //Sets the Viewport using the Width and Height Variables
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void GameDisplay::SwapBuffers()         //Swaps the Display Buffers
{
	SDL_GL_SwapWindow(GameWindow);  //Swaps the Buffers 
}