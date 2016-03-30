#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Material.h"
#include "Vertex.h"

struct ObjModelIndex
{
	int position;
	int texture;
	int normal;
	int material;
};

struct ObjModel
{
public:
	ObjModel(const std::string& filePath);

private:
	void CreateFace(int materialIndex, const std::string& line);

public:
	std::vector<ObjModelIndex> indices;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<Material*> materials;
};
