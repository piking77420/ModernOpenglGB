#pragma once

#include<vector>
#include<Core/Debug/LogClass.h>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<Ressources/Texture/Texture.hpp>
#include "LowRenderer/RendererComponent/RendererComponent.h"

#include<LowRenderer/Material/Material.h>
#include<Core/DataStructure/Component/Component.h>



class RendererComponent;
class Texture;
class Entity;
class Model;
class Transform;
class Vertex;
class AppData;



class MeshRenderer : public RendererComponent
{
public:
	void Draw(Scene* scene, Shader* shader) override;
	void MeshRendererDrawStencil(Scene* scene, Shader* shader);
	void ImguiWindowComponents() override;
	MeshRenderer(const Model& modelToCopy, const Texture& _textures, Entity& entityAttach);
	~MeshRenderer();

	 std::vector<uint32_t> indexVector;
	 Material material;

private:

	void MeshRendererDraw(Scene* scene, Shader* shader);
	const Model* m_Model;
	Texture texture;
};

