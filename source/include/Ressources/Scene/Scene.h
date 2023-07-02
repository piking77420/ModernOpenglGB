#pragma once
#include<vector>
#include "Ressources/IResources/IResource.h"
#include <unordered_map>
#include "Physics/PhysicsEngine.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>

class Transform;
class MeshRenderer;
class Entity;
class AppData;
class FrameBuffer;

class Scene : public IResource
{
public :

	void RenderScene(Shader* shaderProgramm, Shader* StencilShader);
	void RenderGizmo(Shader* shaderProgramm);
	void RenderUi(Shader* shaderProgramm);
	void FixedUpdate();
	void SceneUpdate(ImGuiIO& _io);
	void SaveScene();

	void AddEntity();
	void RemoveEntity(Entity* entity);

	


	uint32_t GlobalID;
	std::string name;
	PhysicsEngine m_PhysicsEngine;
	ImGuiIO* io;
	Camera* cam;
	const float FixedDeltatime = 0.016f;
	float  Deltatime;

	static RessourcesManager* ressourcesManagers;
	std::vector<Entity*> entities;
	static FrameBuffer* OpenGlRenderToImgui;

	Scene(std::string Filename);
	Scene();	
	~Scene();

private:

};

