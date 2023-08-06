
#pragma once
#include "Core/ECS/IECSSystem.h"
#include <string>

class Shader;
class Scene;
class DirectionalLight;
class PointLight;
class SpothLight;

class RendererShadowSystem : public IEcsSystem
{ 
public:
	static inline bool boolHasDrawBuffer = false;
	ImplementIEcsSystem;
private:
	Shader* depthShader;
	Scene* currentScene;


	void CalCulateDepthBufferDirectionnal();
};

