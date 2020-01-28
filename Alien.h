#pragma once


#include "TransformManager.h"
#include "GameConstants.h"

class Alien
{
public:

	Alien(vec3 position);               //Class Constructor, Takes In the Object Position
	~Alien();                           //Deconstructor
	void Update();                      //Updates the Aliens Position
	TransformManager AlienTransformB ;	//The Aliens Transform

	float Speed = 10.5f;       //The Aliens Speed
	bool IsActive = false;     //Boolen for if the Alien is Currently Active
	bool CollisionDetectionMethod(vec3 ModelPos, float ModelRadius);      //The Collision Detection Method 
	float FindLength(vec3(ObjectLength));                                   //Calculates the Length of the Object Squared
};