
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
	void CalCulateDepthBufferPointLight(Scene* scene);
	void CalCulateDepthBufferSpothLight(Scene* scene);

	void ResetViewPort() const;

};

