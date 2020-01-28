

#include "GameConstants.h"
#include "GameSound.h"

using namespace std;

class SoundManager       //Sound Manager Class
{
private:
	static SoundManager* sInstance;        //Creates the Instance of the Sound Manager
	ALCcontext *OALContext;                //Assigns the Context
	ALCdevice *OALDevice;                   

protected: 
	SoundManager();                        //Class Construcor
	~SoundManager();                       //Class Destructor
	map <LPCSTR, GameSound*> gameSnds;     //Maps the Game sounds
	void CreateContext();                  //Method for Creating the Context
	  
public: 
	void AddSound(LPCSTR sndName, LPCSTR fileName);     //Loads the Sound to the game from File
	GameSound* getSnd(LPCSTR sndName);                  //Finds the Sound
	void DeleteSound();                                 //Deletes the Sound
	static SoundManager* getInstance();                 //Finds the Sound Manager Instance
	bool AudioMuted = false;                            //Checks if the Audio is Muted

};
