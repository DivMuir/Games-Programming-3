#include "InputManager.h"
#include <iostream>

InputManager* InputManager::Instance = NULL;         //Clears the Instance of the Input Manager

InputManager::InputManager()       //Class Constructor
{
	
}
InputManager::~InputManager()	   //Class Destructor
{

}

InputManager* InputManager::GetInstance()
{
	if (Instance == NULL)                   //If there isn't an Instance for the Input Manager
	{
		Instance = new InputManager();      //A new Instance is Created
	}
	return Instance;	                    //Returns the new Instance
}


bool InputManager::isKeyDown(SDL_Scancode sdlcode)       //Method for checking if a key is being pressed
{
	return KeyStates[sdlcode];	                         //Returns the Key state of the Key being pressed
}

void InputManager::UpdateInput()                        //Method updates the Inputs
{
	KeyStates = SDL_GetKeyboardState(NULL);             //Resets the Key states 
}

void InputManager::CheckEvents(TransformManager trans, CameraManager* camera)     //Checks for Events Listening for Key presses
{
	static SDL_Event InputEvent;
	while (SDL_PollEvent(&InputEvent))
	{
	}
}


