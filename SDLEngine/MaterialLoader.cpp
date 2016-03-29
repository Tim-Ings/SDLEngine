#include "MaterialLoader.h"
#include <fstream>
#include <iostream>
#include "Error.h"


std::vector<Material*> LoadMaterials(const std::string& workingDir, const std::string& fileName)
{
	std::vector<Material*> materials;
	std::ifstream file;
	file.open((workingDir + "/" + fileName).c_str());

	std::string line;
	if (file.is_open())
	{
		// the current material
		Material* mat = nullptr;

		// material props
		/*std::string matName;
		glm::vec3 ambientColor;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;
		float shininess;
		float transparency;
		Texture* texture;
*/
		while (file.good())
		{
			getline(file, line);

			// don't try and parse a very short line
			if (line.length() < 2)
				continue;

			// get cstr from stdstr
			const char* lineCStr = line.c_str();

			// parse props from line
			switch (lineCStr[0])
			{
			case 'n': // "n..." => newmtl
				// we found new material definition
				mat = new Material();
				materials.push_back(mat);
				mat->name = std::string(lineCStr + 7);
				break;
			case 'K': // "K?" => color ?
				float r, g, b;
				switch (lineCStr[1])
				{
				case 'a': // "Ka" => ambient color
					sscanf_s(lineCStr, "Ka %f %f %f", &r, &g, &b);
					mat->ambientColor = glm::vec3(r, g, b);
					break;
				case 'd': // "Kd" => diffuse color
					sscanf_s(lineCStr, "Kd %f %f %f", &r, &g, &b);
					mat->diffuseColor = glm::vec3(r, g, b);
					break;
				case 's': // "Ks" => specular color
					sscanf_s(lineCStr, "Ks %f %f %f", &r, &g, &b);
					mat->specularColor = glm::vec3(r, g, b);
					break;
				}
				break;
			case 'N': // "Ns" => shininess
				if (lineCStr[1] != 's')
					break;
				sscanf_s(lineCStr, "Ns %f", &mat->shininess);
				break;
			case 'd': // "d" => transparency
				sscanf_s(lineCStr, "d %f", &mat->transparency);
				break;
			case 'T': // "Tr" => transparency
				if (lineCStr[1] != 'r')
					break;
				sscanf_s(lineCStr, "Ns %f", &mat->transparency);
				break;
			case 'm': // "map_Kd" => texture file
				if (lineCStr[1] != 'a')
					break;
				char textureFileName[BUFSIZ];
				sscanf_s(lineCStr, "map_Kd %s", &textureFileName);
				mat->texture.reset(new Texture(workingDir + "/" + textureFileName));
				break;
			};
		}
	}
	else
	{
		fatalError("Unable to load material definition file: " + fileName);
	}

	return materials;
}
