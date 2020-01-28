#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GameConstants.h>
struct TransformManager   //Transform Manager Class
{
private:
	glm::vec3 position;    //Transform Position Value
	glm::vec3 rotation;    //Transform Rotation Value
 	glm::vec3 scale;       //Transform Scale Value

public:

	TransformManager(const vec3& Pos = glm::vec3(), const vec3& Rot = glm::vec3(), const vec3& Scale = vec3(1.0f, 1.0f, 1.0f)) :position(Pos),rotation(Rot),scale(Scale) {}     //Class Constructor

	inline glm::mat4 GetModel() const        //Finds the Model at run time
	{
		//model matrix is calculated
		glm::mat4 PosMatrix = glm::translate(position);                        //The Models Position Matrix
		glm::mat4 ScaleMatrix = glm::scale(scale);                             //The Models Scale Matrix
		glm::mat4 RotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));    //The Models X Rotation
		glm::mat4 RotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));    //The Models Y Rotation
		glm::mat4 RotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));    //The Models Z Rotation
		glm::mat4 RotMatrix = RotX * RotY * RotZ;
		return PosMatrix * RotMatrix * ScaleMatrix;    //The Models Matrix is then Calulated
	}
	inline vec3& GetPos() { return position; }     //Finds the Models Position
	inline vec3& GetRot() { return rotation; }     //Finds the Models Rotation
	inline vec3& GetScale() { return scale; }      //Finds the Models Scale
	inline void SetPos(const vec3& Pos) { this->position = Pos; }      //Sets the Models Position
	inline void SetRot(const vec3& Rot) { this->rotation = Rot; }      //Sets the Models Rotation
	inline void SetScale(const vec3& Scale) { this->scale = Scale; }   //Sets the Models Scale
};

