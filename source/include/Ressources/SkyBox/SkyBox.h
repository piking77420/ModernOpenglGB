#pragma once
#include <glad/glad.h>
#include "Ressources/Mesh/Mesh.h"
#include "Ressources/CubeMaps/CubeMaps.h"

	
class Mesh;

class SkyBox : public Mesh
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

