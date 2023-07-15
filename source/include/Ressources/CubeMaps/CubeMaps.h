#pragma once
#include<vector>
#include<string>
#include<Debug/Debug.h>
#include<glad/glad.h>
#include <filesystem>
#include "Ressources/Texture/Texture.hpp"
namespace fs = std::filesystem;



class CubeMaps  : public IResource
{

public:

	GLuint ID;
	GLenum type;
	GLenum PixelType;

	GLuint format;
	int slot;

	int width;
	int height;
	int nbrOfChannel;


	void BindCubeMap() const;
	void UnBindCubeMap() const;

	
	void operator=(const CubeMaps& cubeMaps);
	CubeMaps(std::vector<std::string> allMapsFile);
	CubeMaps(const fs::path& FilePath);
	CubeMaps(){};
	~CubeMaps();
private:
	static int cubmapGlobalIndex;
};

