#pragma once
#include "GameConstants.h"

class TextureManager     //Texture Manager Class
{
public:
	TextureManager(const std::string& fileName);    //Class Constructor

	void BindTexture(unsigned int unit);            //Binds the Textures
	~TextureManager();                              //Class Destructor

protected:
private:

	GLuint texHandler;             //The Texture Handler
};


