
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
	ImplementIEcsSystem;
private:
	Scene* currentScene;


	void CalCulateDepthBufferDirectionnal(Scene* scene);
};

