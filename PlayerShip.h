#pragma once


#include "TransformManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "GameConstants.h"



class PlayerShip
{

private:

	TransformManager PlayerTransform = vec3 (-50, 0,-350);
	ModelManager* PlayerModel;
	TextureManager* PlayerTexture;

public:


	PlayerShip();

	PlayerShip(const vec3& pos, const string& textureFilename, const string& modelFilename);

	~PlayerShip();

	void Update();
	void Render();

	inline vec3 GetPos();

	TransformManager GetShipTransform()
	{
		return PlayerTransform;
	}


};