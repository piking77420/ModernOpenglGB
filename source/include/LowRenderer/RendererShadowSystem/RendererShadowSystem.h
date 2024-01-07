
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
	virtual void FixedUpdate(Scene* scene) override;

	virtual void Render(Scene* scene) override;
	
private:


	void CalCulateDepthBufferDirectionnal(Scene* scene);
	void CalCulateDepthBufferPointLight(Scene* scene);
	void CalCulateDepthBufferSpothLight(Scene* scene);

	void ResetViewPort() const;

};

