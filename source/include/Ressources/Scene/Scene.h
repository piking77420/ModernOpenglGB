#pragma once
#include<vector>
#include "Ressources/IResources/IResource.h"
#include <unordered_map>
#include "Physics/PhysicsEngine.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "LowRenderer/Gizmo/Gizmo.h"

// ECS // 
#include "Core/ECS/Register.h"

#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>


class FrameBuffer;

class Scene : public IResource
{
public :


	void Init();

	void Awake();
	void Start();


	void FixedUpdate();
	void Update();
	void LateUpdate();

	void Render();


	Register m_register;
	std::string name;
	ImGuiIO io;
	Camera* cam;
	const float FixedDeltatime = 0.016f;
	float  Deltatime;

	static RessourcesManager* ressourcesManagers;
	static FrameBuffer* OpenGlRenderToImgui;

	Scene(const fs::path& FilePath);
	~Scene();

private:

};

