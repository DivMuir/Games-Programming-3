#pragma once

#include "GameConstants.h"
class GameSound   //Game Sound Class
{
private:
	char*        OALData;           //Audio Data
	ALenum       OALFormat;         //Buffer format
	ALsizei      OALFrequency;      //Audio Frequency
	long         OALBufferLen;      //Audio Bit depth
	int			 OALChannels;		//Audio Channels
	int			 OALSize;			//Audio Size
	int			 OALBitRate;		//Audio Bit Rate
	float        OALLength;		    //Audio Length
	ALboolean    OALLoop;           //Does the Audio loop
	unsigned int OALSource;         //The Audio source
	ALuint       OALBuffer;         //Audio Buffer
	ALboolean    OALbEAX;			//Checks for EAX 2.0 support
	ALboolean    alLoop;			//Does the Audio loop

	struct FMTCHUNK {
		short format;
		short channels;
		unsigned long srate;
		unsigned long bps;
		short balign;
		short samp;
	};

	void LoadWAVInfo(ifstream &filename, string &name, unsigned int &size);          //Loads the Audio from File

public:

	GameSound();            //Class Constructor
	~GameSound();           //Class Destructor

	void LoadWAVFile(LPCSTR filename);	//Loads the Audio from File
	void PlayAudio(ALboolean sndLoop);	//Plays the Audio File
	void StopAudio();	                //Stops the Audio
	void CleanUp();	                    //Deletes Unused Data
	bool IsPlaying();                   //Checks if Audio is Playing
};