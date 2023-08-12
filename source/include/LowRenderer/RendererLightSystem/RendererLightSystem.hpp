#pragma once
#include "Core/ECS/IECSSystem.h"
#include <string>

class Shader;
class Scene;
class DirectionalLight;
class PointLight;
class SpothLight;


class RendererLightSystem : public IEcsSystem
{
public:
	ImplementIEcsSystem;
private:
	void UpdateDirectionnalLights(std::vector<uint8_t>* data, Scene* scene);
	void UpdatePointLights(std::vector<uint8_t>* data, Scene* scene);
	void UpdateSpothLights(std::vector<uint8_t>* data,Scene* scene) ;




	void RenderDirectionalLight(const DirectionalLight* dirLight, Scene* scene);


	const Shader const* currentShader;
	Scene* currentScene;


};

