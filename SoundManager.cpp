
#include "SoundManager.h"

SoundManager* SoundManager::sInstance = NULL;     //Clears the Sound Manager Instance

SoundManager::SoundManager()   //Class Constructor
{
	CreateContext();      //Creates the Sound Context
}
SoundManager* SoundManager::getInstance()   //Finds the Sound Manager Instance
{
	if (sInstance == NULL)                  //If there isn't an Instance of the Sound Manager
	{
		sInstance = new SoundManager();     //A New instance is created
	}
	return SoundManager::sInstance;         //Returns with the Instance
}

void SoundManager::CreateContext()           //Method for Creating the Context
{
	OALDevice = alcOpenDevice(NULL);         
	if (OALDevice)
	{
		OALContext = alcCreateContext(OALDevice, NULL);  //Creates the Context
		alcMakeContextCurrent(OALContext);               //Makes it the Active Context
	}
}

void SoundManager::AddSound(LPCSTR sndName, LPCSTR fileName)     //Adds a sound File to the Game from File
{
	if (!getSnd(sndName))                                   //If there isn't a sound file with the same name
	{
		GameSound * newSnd = new GameSound();               //Create a new sound
		newSnd->LoadWAVFile(fileName);                      //Load the Sound from File
		gameSnds.insert(make_pair(sndName, newSnd));        //Attach the Sound 
	}
}

GameSound* SoundManager::getSnd(LPCSTR sndName)                           //Finds the Sound
{
	if (!AudioMuted)                                                           //If Audio is not Muted
	{
		map<LPCSTR, GameSound*>::iterator snd = gameSnds.find(sndName);        //Maps the Sound
		if (snd != gameSnds.end())                                             
		{
			return snd->second;
		}
		else
		{
			return NULL;
		}
	}
}

void SoundManager::DeleteSound()         //Deletes the Sound
{
	for (map<LPCSTR, GameSound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)     //For Each Sound in the Array 
	{
		delete snd->second;    //Delete the Sound
	}
}

SoundManager::~SoundManager()                        //Class Destructor
{
	OALContext = alcGetCurrentContext();             //Gets the Current Context
	OALDevice = alcGetContextsDevice(OALContext);   //Gets the Device for the current Context
	alcDestroyContext(OALContext);                  //Deletes the Context
	alcCloseDevice(OALDevice);                      //Closes the Device
}