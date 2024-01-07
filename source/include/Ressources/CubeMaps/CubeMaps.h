#pragma once
#include<vector>
#include<string>
#include<Debug/Debug.h>
#include<glad/glad.h>
#include <filesystem>
#include "Ressources/Texture/Texture.hpp"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
namespace fs = std::filesystem;



class CubeMaps  : public IResource
{

public:



	virtual void BindCubeMap() const;
	virtual void UnBindCubeMap() const;
	virtual void InitResource() override;

	
	void operator=(const CubeMaps& cubeMaps);
	CubeMaps(const std::string& hdrMap);

	CubeMaps(){}
	virtual ~CubeMaps();



	TextureFlags flags;
	GLuint ID = 0;
protected:

	int width = 0;
	int height = 0;
	
	int nbrOfChannel = 0;

	void Load(std::vector<std::string>& allMapsFile);
};

