#include "AlienBlastGame.h"


LPCSTR sounds[3] = { "res/Audio/Explosion.wav", "res/Audio/Shooting.wav", "res/Audio/MainMusic.mp3" };
LPCSTR fonts[1] = { "res/Fonts/doctor_who.ttf" };


AlienBlastGame::AlienBlastGame() //Class Constructor
{
	Init();      // Initalises the Game 
}

AlienBlastGame::~AlienBlastGame()  //Class Destructor
{

}

void AlienBlastGame::Init()    //Initialises the Game
{
	
	TheInputManager = InputManager::GetInstance();      //Gets the Instance of the Input Manager
	TheFontManager = FontManager::getInstance();        //Gets the Instance of the Font Manager
	GameWindow = new GameDisplay(SCREENWIDTH, SCREENHEIGHT, "GP3 CourseWork DavidMuir");         //Creates the Game Display Window

	InitiateModels();       //Initiates the Game's Models
 	InitiateTexture();      //Initiates the Game's Textures
	InitiateCameras();      //Initiates the Game's Camera
	InitiateSounds();       //Initiates the Game's Sounds
	InitiateTransforms();   //Initiates the Game Object's Transforms
	GameLoop();             //Starts the Game Loop
}


void AlienBlastGame::InitiateModels()       //Loads all the Game Models from File 
{
	PlayerShipModel = new ModelManager("res/Models/f.obj");      //Loads the model for the Player's Ship
	RocketModel = new ModelManager("res/Models/Rocket.obj");     //Loads the model for the Rockets
	AlienShipModel = new ModelManager("res/Models/viper.obj");   //Loads the model for the Alien Ship
	SunModel = new ModelManager("res/Models/Earth.obj");        //Loads the model for the Sun 
	PlanetModel = new ModelManager("res/Models/PlanetSurface.obj");     //Loads the model for the Planet

	LifeIndicator1 = new ModelManager("res/Models/viper.obj");   //Loads the model for the Life Indicator
	LifeIndicator2 = new ModelManager("res/Models/viper.obj");   //Loads the model for the Life Indicator
	LifeIndicator3 = new ModelManager("res/Models/viper.obj");   //Loads the model for the Life Indicator
}


void AlienBlastGame::InitiateTexture()      // Loads all of the Games Textures from File
{
	PlayerShipTexture = new TextureManager("res/Textures/MetalTexture.jpg");              //Loads the Texture for the Player's Ship
	RocketTexture = new TextureManager("res/Textures/MissileTexture.jpg");      //Loads the Texture for the Rocket
	AlienShipTexture = new TextureManager("res/Textures/MetalTexture.jpg");               //Loads the Texture for the AlienShip
	SunTexture = new TextureManager("res/Textures/SunTexture.jpg");            //Loads the Texture for the Sun
	PlanetTexture = new TextureManager("res/Textures/PlanetTexture.jpg");       //Loads the Texture for the Planet
	LifeIndicatorTexture = new TextureManager("res/Textures/MetalTexture.jpg");           //Loads the Texture for the Life Indicator
}


void AlienBlastGame::InitiateCameras()       // Initiates all the Game Cameras
{
	TopDownCamera = new CameraManager(TopDownCameraTransform.GetPos(), 70.0f, (float)SCREENWIDTH / (float)SCREENHEIGHT, 0.01f, 1000.0f);     //Creates the Top Down Camera
	ThirdPersonCamera = new CameraManager(ThirdPersonCameraTransform.GetPos(), 70.0f, (float)SCREENWIDTH / (float)SCREENHEIGHT, 0.01f, 1000.0f); //Creates the Third Person Camera

    //Loads the Shaders from File
	GameShader = new ShaderManager("res/Shaders/phongShader");    
	GameShader2 = new ShaderManager("res/Shaders/basicShader");    
}





void AlienBlastGame::InitiateSounds()      //Loads all the Game Audio from File
{

	TheSoundManager = SoundManager::getInstance();   //Creates the Instance for the Sound Manager

	TheSoundManager->AddSound("Shoot", sounds[1]);         //Adds the Player shooting sound from File
	TheSoundManager->AddSound("Explosion", sounds[0]);     //Adds the Explision sound from File
	TheSoundManager->AddSound("MainMusic", sounds[2]);     //Adds the Main Music from File
}




void AlienBlastGame::InitiateTransforms()             // Sets the Transform for Game Objects
{
	RocketTransform.SetScale(glm::vec3(5, 5, 5));     //Sets the Scale of the Rocket
	RocketTransform.GetRot().x = 270;                 //Sets the X Rotation of the Rockets

	SunTransfrom.SetScale(glm::vec3(100, 100, 100));
	//SunTransfrom.GetPos().x = TopDownCameraTransform.GetPos().x + 20;    //Sets the Position for the Sun
	SunTransfrom.GetPos().z = TopDownCameraTransform.GetPos().z +800 ;        //Sets the Position for the Sun

	LifeIndicator1Transform.GetRot().y = 180;     //Sets the Rotation of the Life Indicators 
	LifeIndicator2Transform.GetRot().y = 180;    
	LifeIndicator3Transform.GetRot().y = 180;

	PlayerShipTransform.SetScale(glm::vec3(1, 1, 1));  //Sets the Scale of the Player Ship
	PlanetTransform.SetScale(glm::vec3(10, 10, 10));   //Sets the Scale of the Planet
	
}






void AlienBlastGame::GameLoop()       //The Game Loop
{

	TheSoundManager->getSnd("MainMusic")->PlayAudio(AL_TRUE);	 // Start playing the Game's Main Music

	if (TheSoundManager->AudioMuted == true)           // Checks to see if the Game Audio has been muted
	{
		TheSoundManager->getSnd("MainMusic")->StopAudio();   //If so then the Music is stopped
	}
	else                                                       // Otherwise 
	{
		TheSoundManager->getSnd("MainMusic")->PlayAudio(AL_TRUE);    // The Music Continues to play
	}

	glPopMatrix();  
	

	while (!GameWindow->IsClosed())           // While the Game Window is active
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();
		GameWindow->SetOrthographicProj(SCREENWIDTH, SCREENHEIGHT);      // Sets up the Orthographic projection for the Window
		
		glPopMatrix();
		GameWindow->SetMVP(SCREENWIDTH, SCREENHEIGHT);                     //Sets the MVP for the Game Window
		UpdateAndRender();	                                               //Updates all the objects on screen and then Draws them in their New positions
		TheInputManager->CheckEvents(PlayerShipTransform, TopDownCamera);  //Checks for Player INput
		CheckCollisions();                                                 //Checks for Collisions
		TheInputManager->UpdateInput(); //Update manager
		PlayerControls();                                                  //Carries out Player Inputs

			GameWindow->ClearDisplayColour(0.0f, 0.0f, 0, 1.0f);     //Sets the Game Window Colour to Black
			cout << "Player Lives: " << PlayerLives << "	" << "Wave: " << Level << endl;   // Prints the Player Lives and Current wave to the Command Line
		}
	}



	void AlienBlastGame::PlayerControls()        // The Control Methods
	{

		if (ThirdPerson)                      //And If Third Person is True
		{


			if (TheInputManager->isKeyDown(SDL_SCANCODE_W))        //If the Player presses W
			{
				if (PlayerShipTransform.GetPos().x <= 50.5)        //And if the Player's Ship is not outside of the screen bounds
				{
					PlayerShipTransform.GetPos().x += 0.5f;        //The Ship Moves up the Screen
				}
			}

			if (TheInputManager->isKeyDown(SDL_SCANCODE_S))         //If the Player presses S
			{
				if (PlayerShipTransform.GetPos().x >= -50.5)        //And if the Player's Ship is not outside of the screen bounds
				{
					PlayerShipTransform.GetPos().x -= 0.5f;         //The Ship Moves down the Screen
				}
			}
		}
		else
		{
			if (TheInputManager->isKeyDown(SDL_SCANCODE_A))        //If the Player presses W
			{
				if (PlayerShipTransform.GetPos().x <= 50.5)        //And if the Player's Ship is not outside of the screen bounds
				{
					PlayerShipTransform.GetPos().x += 0.5f;        //The Ship Moves up the Screen
				}
			}

			if (TheInputManager->isKeyDown(SDL_SCANCODE_D))         //If the Player presses S
			{
				if (PlayerShipTransform.GetPos().x >= -50.5)        //And if the Player's Ship is not outside of the screen bounds
				{
					PlayerShipTransform.GetPos().x -= 0.5f;         //The Ship Moves down the Screen
				}
			}
		}

			if (PlayerShipTransform.GetPos().x >= 50.5)             //If the Players Ship is outside the Screen bounds then 
			{
				PlayerShipTransform.GetPos().x = 50.4f;             //It it is Set back onto the Screen
			}

			if (PlayerShipTransform.GetPos().x <= -50.5)            //If the Players Ship is outside the Screen bounds then
			{
				PlayerShipTransform.GetPos().x = -50.4f;            //It it is Set back onto the Screen
			}
		

		if (TheInputManager->isKeyDown(SDL_SCANCODE_SPACE))     //If the Player Presses Space
		{
			if (!RocketFired)                                   //If the Rocket hasn't been fired
			{
				TheRockets.push_back(new Rocket(PlayerShipTransform));    //A new rocket is Instantiated and added onto the Rocket Array
				int NumberOfRockets = TheRockets.size() - 1;              //The Number of Rockets is set to the 
				TheRockets[NumberOfRockets]->IsActive = true;             //Sets the Rocket to Active
				TheSoundManager->getSnd("Shoot")->PlayAudio(AL_TRUE);     //Plays the Rocket Shoot Sound
				RocketFired = true;    //The Rocket Fired is set to True
				Timer = ReloadTimer;   //Reload Timer is started
			}
		}
		else if (Timer > 0)
		{
			Timer -= 0.1f;
		}
		else
		{
			RocketFired = false;    //Reloads the Rocket
		}
		



		if (TheInputManager->isKeyDown(SDL_SCANCODE_C))                      //If the Player presses C
		{
			TheInputManager->SwitchCamera = false;                           //Switch Camera is set to false
			//TransformManager tempTrans = TopDownCameraTransform.GetPos();    //
			if (!SwitchCamera)                        //If Switch Camera is false
			{ 
				if (ThirdPerson)                      //And If Third Person is True
				{
					ThirdPerson = false;              //Third Person is then set to false
				}
				else                                  //OtherWise
				{
					ThirdPerson = true;               //Third Person is set to true
				}
				SwitchCamera = true;                  //Switch Camera is set to True
				CameraSwitchDelay = ReloadTimer;      //Camera Delay is then set 
			}
		}  
		else if (CameraSwitchDelay > 0)       //If the Camera switch delay is above 0 
		{
			CameraSwitchDelay -= 0.1f;        //Then the delay is reduced
		}
		else                                  //Otherwise 
		{
			SwitchCamera = false;             //Switch Camera is set to false
		}

		
		if (TheInputManager->isKeyDown(SDL_SCANCODE_M))        //If the Player presses M
		{ 
			AudioMuted = false;
			if (TheSoundManager->AudioMuted == false)          //If the Audio is not Muted
			{
				TheSoundManager->AudioMuted = true;            //Then the Audio is muted
			}
			else                                               //Otherwise
			{
				TheSoundManager->AudioMuted = false;           //The Audio is UnMuted
			}
		}

	
		if (TheInputManager->isKeyDown(SDL_SCANCODE_ESCAPE))        // If the Player presses the Escape Key
		{
			SDL_Quit();    // The Game Window is closed
		}
	}




void AlienBlastGame::CheckCollisions()       // Collision Detection for the Game
{
	
	//Collision detection is checked between the Players Rockets and the Alien's ship
	for (vector<Rocket*>::iterator RocketIterartor = TheRockets.begin(); RocketIterartor != TheRockets.end(); ++RocketIterartor)           //For each Rocket in the rocket in the Array
	{
		(*RocketIterartor)->Update();                                                                                                      //Update the Rockets Position
		for (vector<Alien*>::iterator AlienIterator = TheAliens.begin(); AlienIterator != TheAliens.end(); ++AlienIterator)                //For each Alien in the Alien Array
		{ 
			if ((*AlienIterator)->CollisionDetectionMethod((*RocketIterartor)->RocketTransformB.GetPos(), 2.5f))                           //If the Aleins Ship collides with a rocket
			{
				(*AlienIterator)->IsActive = false;                                                                                        //The Alien Ship is Deactivated
				(*RocketIterartor)->IsActive = false;                                                                                      //The Rocket is Deactivated
				TheSoundManager->getSnd("Explosion")->PlayAudio(AL_TRUE);                                                                  //The Explosion sound is played
			}
		}
	}

}

void AlienBlastGame::UpdateAndRender()         // Updates the Game Objects Positions and then Renders them
{

	ThirdPersonCameraTransform.GetPos().x = PlayerShipTransform.GetPos().x;
	ThirdPersonCameraTransform.GetPos().y = PlayerShipTransform.GetPos().y + 5;
	ThirdPersonCameraTransform.GetPos().z = PlayerShipTransform.GetPos().z-10 ;
	CameraManager TopDownCamera(TopDownCameraTransform.GetPos(), 70.0f, (float)SCREENWIDTH / (float)SCREENHEIGHT, 0.01f, 1000.0f);      //Initialises the Top Down Camera
	CameraManager ThirdPersonCamera(ThirdPersonCameraTransform.GetPos(), 70.0f, (float)SCREENWIDTH / (float)SCREENHEIGHT, 0.01f, 1000.0f);     //Initialises the Third Person Camera
	CameraManager SelectedCamera;                        //The Current Camera

	if (ThirdPerson)                                     //If the Third Person Camera has been selected
	{
		TopDownCamera.ChangeCameraSettingsToTop();       //The Camera's settings are changed 
		SelectedCamera = TopDownCamera;                  //The Seleceted Camera is switched to the Top Down Camera
	}
	else                                                 //OtherWise
	{
		ThirdPersonCamera.ChangeCameraSettingsTo3rd();   //The Camera's settings are changed to the Third Person settings
		SelectedCamera = ThirdPersonCamera;              //The Selected Camera is switched to the Third Person Camera
	}

	SunTransfrom.GetRot().y += 0.2f;

	GameShader->BindShader();                                                 //Binds the Shader
	GameShader->Update(PlayerShipTransform, SelectedCamera, phongLight);      //Updates the Shader
	PlayerShipTexture->BindTexture(0);                                        //Binds the Player Ship Texture
	PlayerShipModel->RenderMesh();                                            //Renders the Player Ship Model

	GameShader->BindShader();                                                 //Binds the Shader
	GameShader->Update(SunTransfrom, SelectedCamera, phongLight);            //Updates the Shader
	SunTexture->BindTexture(0);                                              //Binds the Sun Texture
	SunModel->RenderMesh();                                                  //Renders the Sun Model
	
	GameShader2->BindShader();                                                //Binds the Shader
	GameShader2->Update(PlanetTransform, SelectedCamera);                     //Updates the Shader
	PlanetTexture->BindTexture(0);                                            //Binds the Planet Texture
	PlanetModel ->RenderMesh();                                               //Renders the Planet Model






	if (PlayerLives == 1)
	{
		GameShader->BindShader();                                              //Binds the Shader
		GameShader->Update(LifeIndicator1Transform, TopDownCamera);            //Updates the Shader
		LifeIndicatorTexture->BindTexture(0);                                  //Binds the Player Life Indicator Texture
		LifeIndicator1->RenderMesh();                                          //Renders the Player Life Indicator Model
	}

	if (PlayerLives == 2)
	{
		GameShader->BindShader();											   //Binds the Shader
		GameShader->Update(LifeIndicator1Transform, TopDownCamera);            //Updates the Shader
		LifeIndicatorTexture->BindTexture(0);                                  //Binds the Player Life Indicator Texture
		LifeIndicator1->RenderMesh();                                          //Renders the Player Life Indicator Model  

		GameShader->BindShader();											    //Binds the Shader
		GameShader->Update(LifeIndicator2Transform, TopDownCamera);             //Updates the Shader
		LifeIndicatorTexture->BindTexture(0);                                   //Binds the Player Life Indicator Texture
		LifeIndicator2->RenderMesh();                                           //Renders the Player Life Indicator Model

	}

	if (PlayerLives == 3)
	{

		GameShader->BindShader();												  //Binds the Shader
		GameShader->Update(LifeIndicator1Transform, TopDownCamera);               //Updates the Shader
		LifeIndicatorTexture->BindTexture(0);                                     //Binds the Player Life Indicator Texture
		LifeIndicator1->RenderMesh();                                             //Renders the Player Life Indicator Model

		GameShader->BindShader();												  //Binds the Shader
		GameShader->Update(LifeIndicator2Transform, TopDownCamera);               //Updates the Shader
		LifeIndicatorTexture->BindTexture(0);                                     //Binds the Player Life Indicator Texture
		LifeIndicator2->RenderMesh();                                             //Renders the Player Life Indicator Model

		GameShader->BindShader();                                                  //Binds the Shader
		GameShader->Update(LifeIndicator3Transform, TopDownCamera);                //Updates the Shader
		LifeIndicatorTexture->BindTexture(0);                                      //Binds the Player Life Indicator Texture
		LifeIndicator3->RenderMesh();                                              //Renders the Player Life Indicator Model
	}




	if (GameStart)
	{

		if (GameStarted)
		{
			system("CLS");
			GameStarted = false;     //Game Started is set to false
			Level++;                 //The Level is Increased
			for (int i = 0; i < SpawnCount; i++)                                                     //For Each Number of Enemy that should be spawned
			{
				TheAliens.push_back(new Alien(vec3((rand() % 230) - 100, 0, rand() % 100 +100)));    //A new Alien Ship is instantiated and added to the Alien Vector
				TheAliens[i]->Speed += (float)(rand() % 5 + 2) / 10;                                 //The Alien ship's Speed is set 
				TheAliens[i]->IsActive = true;                                                       //The Alien Ship is Set to Active
				AliensAlive++;                                                                       //The Alien Counter is Increased by 1
			}
		}

		else                                                                                         //Otherwise
		{
			if (AliensAlive <= 0)                       //If all the Aliens are Dead 
			{
				TheAliens.clear();                      //Clear the Aliens array
				SpawnCount += rand() % 3 + 1;           //Increase the number of Enemies that spawn
				if (SpawnCount >= 7)                    //Limits the Total number of Aliens that can spawn
				{
					SpawnCount = 7;                     //Up to 7 Aliens can spawn
				}
				GameStarted = true;                   
			}
		}


	}


	//Updates and Renders the Alien

	for (vector<Alien*>::iterator AlienIter = TheAliens.begin(); AlienIter != TheAliens.end(); AlienIter++)                     //For each Alien in the array
	{
		if ((*AlienIter)->IsActive)                                                                                             //If the Alien is Active
		{ 
			if ((*AlienIter)->AlienTransformB.GetPos().x >= 50.5f || (*AlienIter)->AlienTransformB.GetPos().x <= -50.5f)        //If the Alien is outside the bounds of the screen
			{
				(*AlienIter)->AlienTransformB.GetPos().x = 0;                                                                   //Resets the Aliens position in the Screen
			}
			(*AlienIter)->Update();                                                                                             //Updates the Aliens Position
			GameShader->BindShader();                                                                                           //Binds the Shader
			GameShader->Update((*AlienIter)->AlienTransformB, SelectedCamera);                                                  //Updates the Shader
			AlienShipTexture->BindTexture(0);                                                                                   //Binds the Alien Ship Texture 
			AlienShipModel->RenderMesh();                                                                                       //Renders the Alien Ship
		}
	}

	//Updates and Renders the Rocket

	for (vector<Rocket*>::iterator RocketIter = TheRockets.begin(); RocketIter != TheRockets.end(); RocketIter++)               //For each Rocket in the Array
	{
		if ((*RocketIter)->IsActive)                                                                                            //If the Rocket is Active
		{
			(*RocketIter)->Update();                                                                                            //Update the Rocket
			GameShader->BindShader();                                                                                           //Bind the Shader
			GameShader->Update((*RocketIter)->RocketTransformB, SelectedCamera);                                                //Update the Shader
			RocketTexture->BindTexture(0);                                                                                      //Bind the Rocket Texture
			RocketModel->RenderMesh();                                                                                          //Render the Rocket Model
		}
	}


	//Rocket Active Check

	vector<Rocket*>::iterator RocketIter = TheRockets.begin();                 //For each Rocket in the Array
	while (RocketIter != TheRockets.end())                                     //While not at the end of the array
	{
		if ((*RocketIter)->IsActive == false)                                  //If the Rocket isn't Active
		{
			RocketIter = TheRockets.erase(RocketIter);                         //The Rocket is Removed from the Array
		}
		else                                                                   //Otherwise 
		{
			RocketIter++;                                                      //Move to the next Rocket in the Array
		}
	}


	//Alien Active Check

	vector<Alien*>::iterator AlienIterartor = TheAliens.begin();               //For each Alien in the Array 
	while (AlienIterartor != TheAliens.end())                                  //While not at the end of the Array
	{
		if ((*AlienIterartor)->AlienTransformB.GetPos().z <= -80)              //If the Alien is outside the bounds of the screen
		{
			PlayerLives --;                                                    //Remove a live from the player
			system("CLS");                                     

			(*AlienIterartor)->IsActive = false;                               //Deactivates the Alien
		}

		if ((*AlienIterartor)->IsActive == false)                              //If the Alien is deactivated 
		{
			AliensAlive--;                                                     //Lower the Number of Aliens alive
			AlienIterartor = TheAliens.erase(AlienIterartor);                  //Remove the Alien from the Array
		}
		else                                                                   //Otherwise
		{ 
			AlienIterartor++;                                                  //Move onto the next Alien in the array
		}
	}

	



	if (PlayerLives <=0)                                                       //If the Player Runs out of lives
	{ 

		cout << "GAME OVER" << endl;                                           //Display Game Over to the Console
		cout << "You survived until wave " << Level << flush << endl;          //Display what wave the player survived to
		system("CLS"); 
		GameWindow->~GameDisplay();                                            // Closes the Game Window
	}


	glEnd();     



	GameWindow->SwapBuffers();      //Swaps the buffer

}