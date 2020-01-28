#pragma once
#include "AlienBlastGame.h"
#include "SDL2\SDL.h"

#undef main

int main(int argc, char *argv[])      //Runs at the Start of the Game
{

	AlienBlastGame BootStrap;
	BootStrap.GameLoop();       //Calls the Game Loop Method

	return 0;
};