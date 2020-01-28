#pragma once

#include <glm\glm.hpp>
#include "GameConstants.h"
#include "obj_loader.h"

class VertexManager  //Vertex Manager Class
{
private:
	vec3 position;   //Model Position
	vec2 texCoord;   //Model Texture Co-Ordinates
	vec3 normal;     //Models Normals
public:
	
	VertexManager(const vec3& position, const vec2& textureCoord, const  vec3& normal = vec3(0, 0, 0))    //Class Constructor
	{
		this->position = position;       //Sets the Models Position
		this->texCoord = textureCoord;   //Sets the Models Texture Co-Ordinates
		this->normal = normal;           //Sets the Models Normals
	}

	inline vec3* GetPosition()  {return &position;}     //Finds the Models Position
	inline vec2* GetTexCoord()  {return &texCoord;}     //Finds the Models Texture Co-Ordinates
	inline vec3* GetNormal()    {return &normal;}       //Finds the Models Normals

};

class ModelManager      //Model Manager Class
{
private:

	void InitMesh(const IndexedModel& model);     //Method for Initalising the Model Mesh
	enum //Enum flags
	{
		POSITION,
		TEX_COORD,
		INDEX,
		NORMAL,
		N_BUFFERS
	};
	GLuint m_VAO;
	GLuint m_VAB[N_BUFFERS];
	unsigned int m_theDrawCount;
	void SendDataToGPU(IndexedModel model);        //Method for sending the Model to the GPU

public:
	ModelManager();                                                                                                //Class Constructor
	ModelManager(const string& fileName);                                                                          //Class Constructor 
	~ModelManager();                                                                                               //Class Destructor

	void RenderMesh();        //Method for Rendering the Model
};
