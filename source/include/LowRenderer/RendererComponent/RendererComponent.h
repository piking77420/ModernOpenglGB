#pragma once


#include<vector>
#include<Core/Debug/LogClass.h>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include<Ressources/Texture/Texture.hpp>

#include<LowRenderer/Material/Material.h>
#include<Core/DataStructure/Component/Component.h>

class Entity;
class Transform;
class Vertex;
class AppData;

class RendererComponent : public Component
{

public:
	virtual void Draw(Scene* scene, Shader* shader);
	void ImguiWindowComponents() override;

	bool StencilTest;
	 RendererComponent(Entity& entityAttach);
	~RendererComponent();

	std::vector<Vertex> vertexVector;
	static RessourcesManager* ressourcesManager;

private:


};

