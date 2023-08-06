#pragma once
#include "ImguiLayer.h"
#include <vector>
#include "UI/InspectorSelectable.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
class App;
class Project;
class Entity;

class DockingSystem
{
public:
	void UpdateDockSpace(Project& CurrentProject);

	ImGuiWindow* SceneRenderWindow = nullptr;
	InspectorSelectable* Insepctor;
	Entity* entitySelected = nullptr;

	DockingSystem();

private:
	std::vector<ImguiLayer*> ImguiLayers;

};

