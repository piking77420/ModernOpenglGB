#pragma once
#include "Core/ECS/IECSSystem.h"
#include <string>
#include "Core/CoreEngine.h"
class Shader;
class Scene;
class DirectionalLight;
class PointLight;
class SpothLight;


class RendererLightSystem : public IEcsSystem
{
public:
	void Render(Scene* scene) override;
private:
	void UpdateDirectionnalLights(std::vector<DirectionalLight>* data, Scene* scene);
	void UpdatePointLights(std::vector<PointLight>* data, Scene* scene);
	void UpdateSpothLights(std::vector<SpothLight>* data,Scene* scene) ;


	void RenderDirectionalLight(const DirectionalLight* dirLight, Scene* scene);

	const Shader* currentShader;

	Scene* currentScene;


};

