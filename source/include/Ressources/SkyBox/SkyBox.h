#pragma once
#include <glad/glad.h>
#include "Ressources/Mesh/Mesh.h"
#include "Ressources/CubeMaps/CubeMaps.h"

	

class SkyBox 
{	
public : 

	SkyBox() {};
	~SkyBox();
	CubeMaps* cubemap = nullptr;
	void operator=(const SkyBox& skybox);


	
private: 
};

