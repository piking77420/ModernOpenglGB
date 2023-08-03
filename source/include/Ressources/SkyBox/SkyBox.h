#pragma once
#include <glad/glad.h>
#include "Ressources/Model/Model.h"
#include "Ressources/CubeMaps/CubeMaps.h"

	


class SkyBox : public Model
{	
public : 
	void Init() override;

	SkyBox(CubeMaps& _cubemaps);
	~SkyBox();
	CubeMaps cubemap;
	void operator=(const SkyBox& skybox);
private: 
	static float CUBEMAPSIZE;
};

