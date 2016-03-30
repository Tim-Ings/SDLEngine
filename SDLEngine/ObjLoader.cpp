#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
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
				{
#define TEMP_SSCANF // ~5.5 secs
//#define TEMP_SPLIT // ~10 secs
//#define TEMP_STREAM // ~7.5 secs

#ifdef TEMP_SSCANF
					glm::vec2 vt;
					sscanf_s(lineCStr, "vt %f %f", &vt.x, &vt.y);
					textures.push_back(vt);
#endif // SSCANF
#ifdef TEMP_SPLIT
					textures.push_back(ParseVec2(line));
#endif // TEMP_SPLIT
#ifdef TEMP_STREAM
					std::istringstream issvt(line.substr(2));
					glm::vec2 vt;
					issvt >> vt.x;
					issvt >> vt.y;
					textures.push_back(vt);
#endif // TEMP_STREAM
					break;
				}
				case 'n': // ? == 'n' => vertex normal
				{
#ifdef TEMP_SSCANF
					glm::vec3 vn;
					sscanf_s(lineCStr, "vn %f %f %f", &vn.x, &vn.y, &vn.z);
					normals.push_back(vn);
#endif // SSCANF
#ifdef TEMP_SPLIT
					normals.push_back(ParseVec3(line));
#endif // TEMP_SPLIT
#ifdef TEMP_STREAM
					std::istringstream issvt(line.substr(2));
					glm::vec3 vn;
					issvt >> vn.x;
					issvt >> vn.y;
					issvt >> vn.z;
					normals.push_back(vn);
#endif // TEMP_STREAM
					break;
				}
				case '\t': // ? == ' ' => vertex
				case ' ':
				{
#ifdef TEMP_SSCANF
					glm::vec3 v;
					sscanf_s(lineCStr, "v %f %f %f", &v.x, &v.y, &v.z);
					positions.push_back(v);
#endif // SSCANF
#ifdef TEMP_SPLIT
					positions.push_back(ParseVec3(line));
#endif // TEMP_SPLIT
#ifdef TEMP_STREAM
					std::istringstream issvt(line.substr(2));
					glm::vec3 v;
					issvt >> v.x;
					issvt >> v.y;
					issvt >> v.z;
					positions.push_back(v);
#endif // TEMP_STREAM
					break;
				}
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
				char buffer[BUFSIZ];
				sscanf_s(lineCStr, "mtllib %s", &buffer);
				std::string mtlFileName = std::string(buffer);
				//std::string mtlFileName = SplitString(line, ' ')[1];
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
		std::cerr << "Unable to load obj model: " << fileName << std::endl;
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