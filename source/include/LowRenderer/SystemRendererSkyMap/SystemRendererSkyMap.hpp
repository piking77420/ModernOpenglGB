#pragma once
#include "Core/ECS/IECSSystem.h"

class Shader;
class SkyBox;

class SystemRendererSkyMap : public IEcsSystem
{
public:
	const Shader* shaderProgram = nullptr;
	const SkyBox* skybox = nullptr;

	ImplementIEcsSystem;



	SystemRendererSkyMap(){};
	~SystemRendererSkyMap(){};

};

