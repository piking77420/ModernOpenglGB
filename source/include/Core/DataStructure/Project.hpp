#pragma once 
#include <string>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "Ressources/Scene/Scene.h"
#include "LowRenderer/Cam/Camera.h"
#include "UI/DockingSystem.hpp"
#include "LowRenderer/Renderer/Renderer.hpp"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "LowRenderer/RendererShadowSystem/RendererShadowSystem.h"
namespace fs = std::filesystem;

class RessourcesManager;
class ThreadPool;

class Project
{
public:




	static inline fs::path ProjectFolderDirectory = fs::path("ProjectFolder");
	
	Scene* currentScene;
	
	RessourcesManager ressourcesManager;
	DockingSystem DockingSystem;

	ThreadPool* poolThread;

	std::string ProjectName = "Project";
	Camera* mainCamera;

	void Update();
	


	Project(std::string ProjectPath);
	Project();
	~Project();
	
private:
	void InitScene();
};
