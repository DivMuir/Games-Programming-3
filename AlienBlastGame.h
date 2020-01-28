#pragma once

#include "GameConstants.h"       
#include "GameDisplay.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "TransformManager.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "Rocket.h"
#include "Alien.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "LightManager.h"


class AlienBlastGame
{
public:
	AlienBlastGame();   //Class Constructor
	~AlienBlastGame();  //Class Destructor
	void GameLoop();	//running the game code


private:

	void Init();                //Initialises the Game
	void InitiateModels();	    //Initialises the Game Models
	void InitiateTexture();     //Initialises the Textures
	void InitiateCameras();     //Initialises the Cameras
	void InitiateTransforms();  //Initialises the Object transforms
	void InitiateSounds();      //Initialises the Game Audio

	void PlayerControls();      //Checks for Player Input
	void UpdateAndRender();     //Updates and Renders objects to the Screen
	void CheckCollisions();	    // Carries out Collision Detection

	



	InputManager* TheInputManager;   //Creates the Input Manager
	SoundManager* TheSoundManager;   //Creates the Sounds Manager
	FontManager* TheFontManager;     //Creates the Font Manager

	GameDisplay* GameWindow;	     //Creates the Game Display Window
					
	vector<Rocket*> TheRockets;      //Creates the Array to hold the Rockets
	vector<Alien*> TheAliens;        //Creates the Array to hold the Alien Ships
		
	ModelManager* PlayerShipModel;     //Model for the Players Ship 
	ModelManager* RocketModel;         //Model for the Players Rockets
	ModelManager* AlienShipModel;      //Model for the Enemies Ship
	ModelManager* SunModel;           //Model for the Sun Object
	ModelManager* PlanetModel;         //Model for the Planet Background
	ModelManager* LifeIndicator1;      //
	ModelManager* LifeIndicator2;      //Model for the Players Life Indicatiors
	ModelManager* LifeIndicator3;      //

	//Game Shaders
	ShaderManager* GameShader;     //Sets up the variables for the Game's shaders
	ShaderManager* GameShader2;    //

	//Textures
	TextureManager* PlayerShipTexture;      //Texture for the Player's Ship
	TextureManager* RocketTexture;          //Texture for the Player's Rockets
	TextureManager* AlienShipTexture;       //Texture for the Alien Ship
	TextureManager* SunTexture;            //Texture for the Sun Object
	TextureManager* PlanetTexture;          //Texture for the Planet
	TextureManager* LifeIndicatorTexture;   //Texture for the Life Indicator

	//Camera Transforms
	TransformManager TopDownCameraTransform = glm::vec3(0, 80,0);           //Sets the Top Down Camera transform
	TransformManager ThirdPersonCameraTransform = glm::vec3(PlayerShipTransform.GetPos().x, PlayerShipTransform.GetPos().y, -100);    //Sets the Third person Camera transform

	//Transforms
	TransformManager RocketTransform = glm::vec3(0, 0, 0);                //Sets the Transform for the Player's Rocket
	TransformManager PlayerShipTransform = glm::vec3(0, 0, -70);          //Sets the Transform for the Player's Ship
	TransformManager AlienShipTransform = glm::vec3(0, 0, 0);             //Sets the Transform for the Alien Ship
	TransformManager SunTransfrom = glm::vec3(500, 200,-450);                //Sets the Transform for the Sun
	TransformManager PlanetTransform = glm::vec3(0, -200, 0);             //Sets the Transform for the Planet

	TransformManager LifeIndicator1Transform = glm::vec3(21, 40,25);      //Sets the Transform for the Life Indicator
	TransformManager LifeIndicator2Transform = glm::vec3(21, 40, 30);     //Sets the Transform for the Life Indicator
	TransformManager LifeIndicator3Transform = glm::vec3(21, 40, 35);     //Sets the Transform for the Life Indicator



	//Cameras

	CameraManager* ThirdPersonCamera;   //Initialises the Third Person Camera
	CameraManager* TopDownCamera;       //Initialises the Top Down Camera
	CameraManager* SelectedCamera;      //The Current Camera

	//Lights

	LightManager phongLight;


	
	//Game Values 
	
	bool RocketFired = false;      //Checks if the Player has fired their Rocket
	bool SwitchCamera = false;     //Checks if the Camera is being switched
	bool ThirdPerson = false;       //Checks if the Third Person Camera is selected 
	bool AudioMuted = false;       //Chekcs if the Audio is muted
	bool GameStart = true;         //Checks if the Game starts

	int Level = 0;              //The level that the Player is currently On
	int PlayerLives = 3;        //The Number of lives that the Player has left
	int AliensAlive;            //The Number of Aliens still alive
	int SpawnCount = 2;         //The Number of Alies being spawned at the start of the Round
	bool GameStarted = true;    //Checks if the Game has started

	float Timer = 0;
	float ReloadTimer = 1.0f;       //Time taken to reload the Players Rocket
	float CameraSwitchDelay = 0;    //The Delay between switching Cameras

};