#pragma once

#include "GameConstants.h"
#include "TransformManager.h"
#include "CameraManager.h"

class InputManager     //Input Manager Class
{
private:

	static InputManager* Instance;     //The Instance for the Input Manager
	const Uint8* KeyStates;           

public:

	InputManager();        //Class Constructor
	~InputManager();       //Class Destructor

	static InputManager* GetInstance();	    //Finds the Instance for the Input Manager
	void UpdateInput();	                    //Updates the Key Inputs
	void CheckEvents(TransformManager transform, CameraManager* camera);     //Checks for Events listening for Input
	bool isKeyDown(SDL_Scancode sdlcode);	                                 //Checks if a key is being pressed

	bool StartGame = false;       //Checks if the Game has started
	bool ShootCannon = false;     //Checks if the Cannon has been fired
	bool SwitchCamera = false;    //Checks if the Camera is being Switched
	bool MuteSounds = false;      //Checks if the Audio has been Muted
};