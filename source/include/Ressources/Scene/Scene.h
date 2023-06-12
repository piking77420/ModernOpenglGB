#pragma once
#include<vector>
#include "Ressources/IResources/IResource.h"
#include <unordered_map>
#include "Physics/PhysicsEngine.h"
#include "LowRenderer/RendererComponent/GizmoRenderer/GizmoRenderer.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>

class Transform;
class MeshRenderer;
class Entity;
class AppData;

class Scene : public IResource
{
public :

	void RenderScene(Shader* shaderProgramm, Shader* StencilShader);
	void RenderGizmo(Shader* shaderProgramm);
	void RenderUi(Shader* shaderProgramm);
	void PhyscisUpdate();
	void SceneUpdate(ImGuiIO& _io);
	void LateUpdate();
	void Saving() override;
	virtual IResource* Load(std::string path);


	std::string name;
	PhysicsEngine m_PhysicsEngine;
	ImGuiIO* io;
	Camera* cam;
	const float FixedDeltatime = 0.016f;
	float  Deltatime;
	RessourcesManager* ressourcesManagers;
	std::vector<Entity*> entities;
	Scene(std::string Filename);
	Scene();	
	~Scene();

private:

};

