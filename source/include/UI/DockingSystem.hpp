#pragma once
#include "ImguiLayer.h"
#include <vector>
#include "UI/InspectorSelectable.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "Core/Input/CoreInput.h"
#include "Core/ECS/Entity.h"
class App;
class Project;
class Entity;

class DockingSystem
{
public:
	void UpdateDockSpace(Project& CurrentProject, std::vector<InputEvent*>& inputEvent);
	uint32_t EnitySelectedID = EntityNULL;


	DockingSystem();

private:
	std::vector<ImguiLayer*> ImguiLayers;

};

