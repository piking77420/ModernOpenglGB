#pragma once
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "UI/InspectorSelectable.h"
#include <Core/Debug/Debug.h>

#include "Mathf.h"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "UI/ContentBrowser.h"
#include "Core/ECS/Entity.h"
#include "UI/DockingSystem.hpp"
#include "Core/DataStructure/Project.hpp"

class ResourcesManager;
class Camera;
class Texture;
class Shader;
class Scene;
class Project;
const int windowWidth = 1920;
const int windowHeight = 1080;
const int MSAA = 8;



class App
{
public:	
	static GLFWwindow* InitOpenglImgui();
	void AppUpdate(GLFWwindow* mainWindow);
		
	static inline bool IsMonoThread = false;
	Project CurrentProject;
	App();
	~App();
	
	static void InitEcsComponent();

private:
	static void EnableOpenGl();
	void HandleSwitchMulthiMonoThread(GLFWwindow* mainWindow);
	static void LoadCursorAppCursor(GLFWwindow* window);
	void InitImguiTheme();
	
};

