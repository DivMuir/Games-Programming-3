
#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

#define SCREENWIDTH 1400            //Sets the Game Screen Width
#define SCREENHEIGHT 1000           //Sets the Game Screen Height
#define MODEL_PATH "res/models/"        //Defines the Path Used to find the Game's Model
#define AUDIO_PATH "res/Audio/"         //Defines the Path Used to find the Game's Audio
#define TEXTURE_PATH "res/Textures/"    //Defines the Path Used to find the Game's Textures
#define SHADER_PATH "res/Shaders/"      //Defines the Path Used to find the Game's Shaders

//Links the SDL2 Libraries to the game
#include <SDL2\SDL.h>
#include <SDL2\SDL_events.h>

//Links the OpenGL and Windows Libraries to the Game
#include <GL\glew.h>
#include <Windows.h>

//Links the GLM Maths Library to the Game
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm\gtc\matrix_transform.hpp"

//Links the OpenAL Libraries to the Game
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
#include <OpenAL\alut.h>

//Utilities
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <cassert>

using namespace std;
using namespace glm;

//Sets up the Colours that will be used in the Game

struct lightColour4 
{
	lightColour4(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 0.0f) : r(_r), g(_g), b(_b), a(_a) {}
	float r;	// Red
	float g;	// Green
	float b;	// Blue
	float a;	// Alpha
};

struct colour3f 
{
	colour3f(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f) : r(_r), g(_g), b(_b) {}
	float r;	// Red
	float g;	// Green
	float b;	// Blue
};

#endif 