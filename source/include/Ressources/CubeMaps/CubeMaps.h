#pragma once
#include<vector>
#include<string>
#include<Debug/Debug.h>
#include<glad/glad.h>
#include <filesystem>
#include "Ressources/Texture/Texture.hpp"
namespace fs = std::filesystem;



class CubeMaps : public Texture
{

public:
	void operator=(const CubeMaps& cubeMaps);
	CubeMaps(std::vector<std::string> allMapsFile);
	CubeMaps(fs::path CubepMasFile);
	CubeMaps();
	~CubeMaps();
private:
	static int cubmapGlobalIndex;
};

