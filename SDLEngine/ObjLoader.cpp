#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include "MaterialLoader.h"
#include "SplitString.h"

glm::vec2 ParseVec2(const std::string& line);
glm::vec3 ParseVec3(const std::string& line);


ObjModel* LoadObjModel(const std::string& workingDir, const std::string& fileName)
{
	ObjModel* model = new ObjModel;

	std::ifstream file;
	file.open((workingDir + "/" + fileName).c_str());
	
	int curMaterialIndex = 0;
	std::string line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			unsigned int lineLength = line.length();
			if (lineLength < 2)
				continue;

			const char* lineCStr = line.c_str();

			switch (lineCStr[0])
			{
			case 'v': // "v?" => vertex
			{
				switch (lineCStr[1])
				{
				case 't': // ? == 't' => vertex texture / uv coords
					model->textureCoords.push_back(ParseVec2(line));
					break;
				case 'n': // ? == 'n' => vertex normal
					model->normals.push_back(ParseVec3(line));
					break;
				case '\t': // ? == ' ' => vertex
				case ' ':
					model->vertices.push_back(ParseVec3(line));
					break;
				}
				break;
			}
			case 'f': // 'f' => face
			{
				model->CreateFace(curMaterialIndex, line);
				break;
			}
			case 'm': // 'm' => material template lib 
			{
				if (lineCStr[1] != 't')
					break;
				std::string mtlFileName = SplitString(line, ' ')[1];
				std::vector<Material*> mats = LoadMaterials(workingDir, mtlFileName);
				model->materials.insert(std::end(model->materials), std::begin(mats), std::end(mats));
				break;
			}
			case 'u': // 'u' => usemtl
			{
				if (lineCStr[1] != 's')
					break;
				std::string mtlName = SplitString(line, ' ')[1];
				for (int i = 0; i < model->materials.size(); i++)
				{
					if (model->materials[i]->name == mtlName)
					{
						curMaterialIndex = i;
						break;
					}
				}
				break;
			}
			};
		}
	}
	else
	{
		std::cerr << "Unable to load mesh: " << fileName << std::endl;
	}

	return model;
}


glm::vec2 ParseVec2(const std::string& line)
{
	std::vector<std::string> split = SplitString(line, ' ');

	// type x y
	float x = atof(split[1].c_str());
	float y = atof(split[2].c_str());

	return glm::vec2(x, y);
}


glm::vec3 ParseVec3(const std::string& line)
{
	std::vector<std::string> split = SplitString(line, ' ');

	// type x y z
	float x = atof(split[1].c_str());
	float y = atof(split[2].c_str());
	float z = atof(split[3].c_str());

	return glm::vec3(x, y, z);
}


void ObjModel::CreateFace(int materialIndex, const std::string& line)
{
	// f 1/1/1 2/2/2 3/3/3
	std::vector<std::string> tokens = SplitString(line, ' ');

	for (int i = 1; i < 4; i++)
	{
		std::vector<std::string> subTokens = SplitString(tokens[i], '/');
		ObjIndex index;
		index.material = materialIndex;
		index.vertex = atoi(subTokens[0].c_str()) - 1;
		index.texture = atoi(subTokens[1].c_str()) - 1;
		index.normal = atoi(subTokens[2].c_str()) - 1;
		//indices.push_back(index);

		indices_vertex.push_back(index.vertex);
		indices_texture.push_back(index.texture);
		indices_normal.push_back(index.normal);
		indices_material.push_back(index.material);
	}
}