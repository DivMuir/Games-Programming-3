#include "ModelManager.h"
#include "obj_loader.h"
#include <vector>

ModelManager::ModelManager()    //Class Constructor
{

}

ModelManager::ModelManager(const std::string& fileName)             //Class Constructor
{
	//Indexed model object is defined as converted OBJ found from filename
	IndexedModel model = OBJModel(fileName).ToIndexedModel();          //The Model found from file is convereted into an Indexed Model
	InitMesh(model);                                                   //The Models Mesh is Initialised
}

ModelManager::~ModelManager()                 //Class Destructor
{

	glDeleteVertexArrays(1, &m_VAO);        //Deletes the Vertex Arrays
}

void ModelManager::InitMesh(const IndexedModel& model)        //Initialises the Mesh
{
	m_theDrawCount = model.indices.size();                    //The Draw count is set to the Size of the Model indice Array
	SendDataToGPU(model);                                     //Creates the Buffer and sends the Model Data to the GPU
}

void ModelManager::SendDataToGPU(IndexedModel model)                //Sends the Model Data to the Buffer
{
	//generates the vert array and binds to VAO object
	glGenVertexArrays(1, &m_VAO);           //Generates the Vertex Array
	glBindVertexArray(m_VAO);               //Binds the Vertex Array to the VAO Object

	glGenBuffers(N_BUFFERS, m_VAB);                    //Creates the Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VAB[POSITION]);    //Binds the Buffer to the Position
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() *sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);  //The Model Data is sent to the Buffer

	glEnableVertexAttribArray(0);                                  //Enables the Vertex Array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);         //Sets the Vertex Attrib Pointer

	glBindBuffer(GL_ARRAY_BUFFER, m_VAB[TEX_COORD]);                                                                                
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(N_BUFFERS, m_VAB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VAB[NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VAB[INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}


void ModelManager::RenderMesh()         //Render the Mesh
{
	glBindVertexArray(m_VAO);                                               //Binds the Vertex Array
	glDrawElements(GL_TRIANGLES, m_theDrawCount, GL_UNSIGNED_INT, 0);       //Draws the Model
	glBindVertexArray(0);                                                   //Clears the Array
}