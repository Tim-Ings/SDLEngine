#pragma once
#include <string>
#include <vector>
#include "Material.h"

extern std::vector<Material*> LoadMaterials(const std::string& workingDir, const std::string& fileName);