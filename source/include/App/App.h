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
#include "Core/ThreadPool/ThreadPool.h"

class RessourcesManager;
class Camera;
class Texture;
class Shader;
class Scene;

const int windowWidth = 1920;
const int windowHeight = 1080;
const int MSAA = 8;



class App
{
public:	
		
	static inline bool IsMonoThread = false;
	void AppUpdate(); 
	Project CurrentProject;
	ThreadPool poolThread;
	App(int _WindowX, int _WindowY, ImGuiIO& _io);
	~App();
private:
	const int windowX;
	const int windowY;

};

