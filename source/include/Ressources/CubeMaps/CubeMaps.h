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
	GLenum pixelType;

	GLuint format;
	int slot;

	int width;
	int height;
	int nbrOfChannel;
	GLuint VAO;
	GLuint VBO;

	void BindCubeMap() const;
	void UnBindCubeMap() const;
	void InitResource() override;

	
	void operator=(const CubeMaps& cubeMaps);
	CubeMaps(std::vector<std::string> allMapsFile);
	CubeMaps() {};
	~CubeMaps();
private:
	static inline float cubeMapSize = 250;

};

