#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Material.h"
#include "Vertex.h"

struct ObjIndex
{
	int vertex;
	int texture;
	int normal;
	int material;
};

struct ObjModel
{
public:
	void CreateFace(int materialIndex, const std::string& line);

public:
	//std::vector<ObjIndex> indices;
	std::vector<int> indices_vertex;
	std::vector<int> indices_texture;
	std::vector<int> indices_normal;
	std::vector<int> indices_material;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normals;
	std::vector<Material*> materials;
};

extern ObjModel* LoadObjModel(const std::string& workingDir, const std::string& fileName);