#pragma once
#include <glad/glad.h>
#include "Ressources/Model/Model.h"
#include "Ressources/CubeMaps/CubeMaps.h"

	


class SkyBox : public Model
{	
public : 
	void Draw() const override;
	SkyBox(CubeMaps& cubemaps);
	SkyBox();
	~SkyBox();
	CubeMaps m_Cubemaps;
	void operator=(const SkyBox& skybox);
private: 
	static float CUBEMAPSIZE;
	void InitBufferCubaMaps();
};

