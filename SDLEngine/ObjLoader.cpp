#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include "MaterialLoader.h"
#include "SplitString.h"

glm::vec2 ParseVec2(const std::string& line);
glm::vec3 ParseVec3(const std::string& line);


ObjModel::ObjModel(const std::string& filePath)
{
	// standardise dir seperators
	std::string filePathStd = std::string(filePath);
	std::replace(filePathStd.begin(), filePathStd.end(), '\\', '/');

	// asd/asd/asd/asd/asd/asd/file.obj
	auto tokens = SplitString(filePathStd, '/');
	std::string fileName = tokens[tokens.size() - 1];
	std::string workingDir = filePathStd.substr(0, filePathStd.size() - fileName.size());


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
					textures.push_back(ParseVec2(line));
					break;
				case 'n': // ? == 'n' => vertex normal
					normals.push_back(ParseVec3(line));
					break;
				case '\t': // ? == ' ' => vertex
				case ' ':
					positions.push_back(ParseVec3(line));
					break;
				}
				break;
			}
			case 'f': // 'f' => face
			{
				CreateFace(curMaterialIndex, line);
				break;
			}
			case 'm': // 'm' => material template lib 
			{
				if (lineCStr[1] != 't')
					break;
				std::string mtlFileName = SplitString(line, ' ')[1];
				std::vector<Material*> mats = LoadMaterials(workingDir, mtlFileName);
				materials.insert(std::end(materials), std::begin(mats), std::end(mats));
				break;
			}
			case 'u': // 'u' => usemtl
			{
				if (lineCStr[1] != 's')
					break;
				std::string mtlName = SplitString(line, ' ')[1];
				for (int i = 0; i < materials.size(); i++)
				{
					if (materials[i]->name == mtlName)
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

		ObjModelIndex index;
		index.position = atoi(subTokens[0].c_str()) - 1;
		index.texture = atoi(subTokens[1].c_str()) - 1;
		index.normal = atoi(subTokens[2].c_str()) - 1;
		index.material = materialIndex;

		indices.push_back(index);
	}
}