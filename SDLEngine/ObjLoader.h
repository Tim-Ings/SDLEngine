#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Material.h"
#include "Vertex.h"

struct ObjModel
{
public:
	ObjModel(const std::string& filePath);

private:
	void CreateFace(int materialIndex, const std::string& line);

public:
	std::vector<int> indices_positions;
	std::vector<int> indices_texture;
	std::vector<int> indices_normal;
	std::vector<int> indices_material;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<Material*> materials;
};
