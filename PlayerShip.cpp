#include "PlayerShip.h"





PlayerShip::PlayerShip()
{



}


PlayerShip::PlayerShip(const vec3& pos, const string& textureFilename, const string& modelFilename)
{
	PlayerTransform.SetScale(vec3(1, 1, 1));
	PlayerModel = new ModelManager("res/Models/PlayerShip.obj");
	PlayerTexture = new TextureManager("res/Textures/MoonTexture.jpg");
}


PlayerShip::~PlayerShip()
{

}



void PlayerShip::Update()
{



}



void PlayerShip::Render()
{
	PlayerTexture->BindTexture(0);
	PlayerModel->RenderMesh();

}

vec3 PlayerShip::GetPos()
{
	return PlayerTransform.GetPos();
	
}

