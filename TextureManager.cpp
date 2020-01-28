
#include "TextureManager.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

TextureManager::TextureManager(const std::string& fileName)
{
	//width height and number of components of image
	int width;              //Width of the Image
	int height;             //Height of the Image
	int numComponents;      //Number of Components in the Image

	unsigned char* imageDat = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);     //Loads the Image from File

	if (imageDat == NULL)                                                //If there is no Image Data
	{
		std::cerr << "texture load failed" << fileName << std::endl;     //Display an Error Message
	}
	glGenTextures(1, &texHandler);                                     //number of and address of texture
	glBindTexture(GL_TEXTURE_2D, texHandler);                          //bind texture, define type and specify the texture we are working on
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);      //Wraps the Textures Outside Width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);      //Wraps the Textures Outside Height
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  //Texture filterning for minification if the Texture is Larger than the Model
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  //Texture filtering for magnification if the Texture is smaller than the Model
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageDat);	    //Sends the Texture to the GPU

	stbi_image_free(imageDat);   //Deletes the Data from the CPU
}

TextureManager::~TextureManager()    //Class Deconstructor
{
	glDeleteTextures(1, &texHandler);     //Deletes the Textures
}

void TextureManager::BindTexture(unsigned int unit)      //Method to bind the Textures
{
	assert(unit >= 0 && unit <= 31);         

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texHandler); 

}