#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Ressources/SkyBox/SkyBox.h"

class Shader;

class SystemRendererSkyMap : public IEcsSystem
{
public:
	const Shader* shaderProgram = nullptr;
		
	virtual void Render(Scene* scene) override;

	SkyBox skybox;


	SystemRendererSkyMap(){};
	~SystemRendererSkyMap(){};

private :
	void DrawCube();

	static inline unsigned int cubeVAO = 0;
	static inline unsigned int cubeVBO = 0;
};

