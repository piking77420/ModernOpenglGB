#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Ressources/CubeMaps/CubeMapHdr.h"

class Shader;

class SystemRendererSkyMap : public IEcsSystem
{
public:
	const Shader* shaderProgram = nullptr;
	CubeMapHdr* cubemap = nullptr;
		
	virtual void Init(Scene* scene) override;
	virtual void Render(Scene* scene) override;
	virtual void Update(Scene* scene) override;

	SystemRendererSkyMap(){};
	~SystemRendererSkyMap(){};


	float irridianceFactor = 1.0f;

private :
	void DrawCubeMap();
	bool m_OpenChangeCubeMap = true;
	

};

