#pragma once
#include "TransformManager.h"
#include "TextureManager.h"
#include "ModelManager.h"

class PlayerLives
{
public:
	PlayerLives (TransformManager PlayerLivesTransform);

	void Update();
	~PlayerLives();

	bool IsActive = false;	// Boolean checks that the bullet is active so that it can be rendered and updated
	
};