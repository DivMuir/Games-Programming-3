#pragma once
#include "TransformManager.h"
#include "TextureManager.h"
#include "ModelManager.h"

class Rocket        //Rocket Class
{
public:
	Rocket(TransformManager PlayerLivesTransform);   //Class Constructor 

	void Update();      //Updates the Rockets Position
	~Rocket();          //Class Destructor

	bool IsActive = false;	 //Bool that checks that the Rocket is Active
	TransformManager RocketTransformB;  //The Rockets Transform
};