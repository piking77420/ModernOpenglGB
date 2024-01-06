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
#include "UI/SceneView.h"


class ResourcesManager;

enum MATERIALSHADER
{
	PHONG,
	PBR,
	MATERIALSHADERSIZE
};


class Project
{
public:

	static inline fs::path projectFolderDirectory = fs::path("ProjectFolder");
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	std::string projectName = "Project";

	
	Scene* currentScene = nullptr;
	ResourcesManager resourcesManager;
	DockingSystem dockingSystem;
	CoreInput coreInput;

	Shader* shaderToRenderer;
	Shader* skybox;

	void Update();
	void Render(SceneView* sceneView);


	Project(std::string ProjectPath);
	Project();
	~Project();
	
	void InitScene();
	static inline MATERIALSHADER shaderType = MATERIALSHADER::PHONG;
private:

	static inline bool Resize;
	static inline int m_Width;
	static inline int m_Height;
};
