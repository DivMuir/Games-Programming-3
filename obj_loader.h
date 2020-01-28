#ifndef OBJ_LOADER_H_INCLUDED
#define OBJ_LOADER_H_INCLUDED

#include <glm/glm.hpp>
#include <GameConstants.h>

struct OBJIndex                  
{
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;

	bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModel                         //Class           
{
public:
	std::vector<glm::vec3> positions;       //The Models Position
	std::vector<glm::vec2> texCoords;       //The Models Texture Co-Ordinates
	std::vector<glm::vec3> normals;         //The Models Normals
	std::vector<unsigned int> indices;      //The Models Indices

	void CalcNormals();                     //Calculates the Models Normals
};

class OBJModel                            //The Model Class
{
public:
	std::vector<OBJIndex> OBJIndices;    //Vector to Hold the Models Indices
	std::vector<glm::vec3> vertices;     //Vector to Hold the Models Vertices
	std::vector<glm::vec2> uvs;          //Vector to Hold the Models UVS
	std::vector<glm::vec3> normals;      //Vector to Hold the Models Normals
	bool hasUVs;                         //Checks if the Model has UVs
	bool hasNormals;                     //Checks if the Model has Normals

	OBJModel(const std::string& fileName);

	IndexedModel ToIndexedModel();
private:

	unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
	void CreateOBJFace(const std::string& line);

	glm::vec2 ParseOBJVec2(const std::string& line);
	glm::vec3 ParseOBJVec3(const std::string& line);
	OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

#endif // OBJ_LOADER_H_INCLUDED