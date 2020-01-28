
#pragma warning ( disable : 4996 )

#include "GameSound.h"
using namespace std;
GameSound::GameSound()   //Class Constructor
{
	OALData = NULL;           //The Audio Data for the Buffer
	OALFrequency = 0;         //The Audio Frequency
	OALBitRate = 0;		      //The Audio Bit Rate
	OALLength = 0;		      //The Audio Length
	OALBuffer = 0;            //The Buffer
}

GameSound::~GameSound()   //Class Destructor
{
	CleanUp();            //Calls the Clean up method
}

void GameSound::LoadWAVFile(LPCSTR filename)        //Method to Load the Audio from File
{
	OALbEAX = alIsExtensionPresent("EAX2.0");     //Checks if EAX2.0 is supported
	alGetError();                                 //CLears any error codes
	
	alutLoadWAVFile((ALbyte *)filename, &OALFormat, (void **)&OALData,(ALsizei *)&OALBufferLen, &OALFrequency, &alLoop);   // Loads the Audio from File
	alGenSources(1, &OALSource);    //Creates the Sound's Source
	alGenBuffers(1, &OALBuffer);    //Creates the Audio Buffer
	alBufferData(OALBuffer, OALFormat, OALData, OALBufferLen, OALFrequency);     //Loads the Data into the Buffer
	alSourcei(OALSource, AL_BUFFER, OALBuffer);     //Assigns the Buffer to the Audio source
	alutUnloadWAV(OALFormat, OALData, OALBufferLen, OALFrequency);   //Deletes the Data
}

void GameSound::LoadWAVInfo(ifstream &filename, string &name, unsigned int &size)   //Finds the Info for the Sounds
{
	char chunk[4];
	filename.read((char *)&chunk, 4);
	filename.read((char *)&size, 4);
	name = string(chunk, 4);
}

void GameSound::PlayAudio(ALboolean sndLoop)      //Method for playing the Audio 
{
	alSourcei(OALSource, sndLoop, AL_TRUE);
	alSourcePlay(OALSource);     //Plays the Sound
}

void GameSound::StopAudio()    //Method for Stopping Audio 
{
	alSourceStop(OALSource);    //Stops playing the Game Sounds
}

void GameSound::CleanUp()     //Method for Cleaning up the program
{
	int state;
	alGetSourcei(OALSource, AL_SOURCE_STATE, &state);   //Finds the Source
	if (state == AL_PLAYING)                            //If Audio is playing
	{ 
		StopAudio();                                    //Stop Playing the Audio
	}
	alDeleteSources(1, &OALSource);                     //Deletes the Audio Source
	alDeleteBuffers(1, &OALBuffer);                     //Deletes the Audio Buffers
	alcMakeContextCurrent(NULL);                        //Removes the Audio Context
	delete OALData;                                     //Delets the Audio Data
}

bool GameSound::IsPlaying()                              //Method for checking if Audio is Playing
{
	ALenum state;
	alGetSourcei(OALSource, AL_SOURCE_STATE, &state);      
	return (state == AL_PLAYING);
}