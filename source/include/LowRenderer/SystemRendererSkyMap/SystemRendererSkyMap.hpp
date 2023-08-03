#pragma once
#include "Core/ECS/IECSSystem.h"

class Shader;
class SkyBox;

class SystemRendererSkyMap : public IEcsSystem
{
public:
	const Shader* shaderProgram = nullptr;
	const SkyBox* skybox = nullptr;

	 void Init(Scene* scene) override ;

	 void Awake(Scene* scene) override ;

	 void Render(Scene* scene) override ;


	SystemRendererSkyMap(){};
	~SystemRendererSkyMap() override {};

};

