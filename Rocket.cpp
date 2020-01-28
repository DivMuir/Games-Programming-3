#include "Rocket.h"

Rocket::Rocket(TransformManager PlayerShipTransformB)           //Class Constructor
{
	
	RocketTransformB.SetScale(vec3(2, 2, 2));                                                                                              //Sets the Rockets Scale
	RocketTransformB.SetPos(vec3(PlayerShipTransformB.GetPos().x, PlayerShipTransformB.GetPos().y , PlayerShipTransformB.GetPos().z));     //Sets the Rockets Position
	RocketTransformB.GetRot().y =90;                                                                                                       //Sets the Rockets Rotation
}

void Rocket::Update()                       // Updates the Rockets Position
{
	RocketTransformB.GetPos().z += 0.5f;    //Moves the Rocket towards the Alien ships 
}

Rocket::~Rocket()           //Class Destructor
{

}

