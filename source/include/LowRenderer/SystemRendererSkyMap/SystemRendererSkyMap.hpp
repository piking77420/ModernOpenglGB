#pragma once
#include "Core/ECS/IECSSystem.h"

class Shader;

class SystemRendererSkyMap : public IEcsSystem
{
public:
	const Shader* shaderProgram = nullptr;
		
	ImplementIEcsSystem;



	SystemRendererSkyMap(){};
	~SystemRendererSkyMap(){};

};

