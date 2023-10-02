#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "ECS/Scene.h"
#include "LowRenderer/Cam/Camera.h"
#include "UI/DockingSystem.hpp"
#include "LowRenderer/Renderer/Renderer.hpp"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "LowRenderer/RendererShadowSystem/RendererShadowSystem.h"
#include "Core/Input/CoreInput.h"
#include "Core/CoreEngine.h"


class ResourcesManager;


class Project
{
public:

	static inline fs::path projectFolderDirectory = fs::path("ProjectFolder");
	
	Scene* currentScene = nullptr;
	
	ResourcesManager resourcesManager;
	DockingSystem dockingSystem;


	std::string projectName = "Project";
	Camera* mainCamera = nullptr;

	CoreInput coreInput;

	Shader* shaderNormal;
	Shader* shaderShadowMapping;
	Shader* skybox;

	void Update();
	Project(std::string ProjectPath);
	Project();
	~Project();
	
	void InitScene();
private:
};
