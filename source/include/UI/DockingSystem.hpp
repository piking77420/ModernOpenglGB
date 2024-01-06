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
#include "UI/SceneView.h"

class App;
class Project;
class Entity;

class DockingSystem
{
public:

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);



	void UpdateDockSpace(Project& CurrentProject);
	void RenderDockSpace(Project& CurrentProject);

	uint32_t EnitySelectedID = EntityNULL;


	DockingSystem();

	void BindDockSpace();
	void UnBindDockSpace();

	template<class T>
	inline ImguiLayer* GetLayer()
	{
		for (size_t i = 0; i < ImguiLayers.size(); i++)
		{
			ImguiLayer* ptr = dynamic_cast<T*>(ImguiLayers[i]);
			if (!ptr)
				return ImguiLayers[i];
		}

		return nullptr;
	}

	SceneView scene;
	SceneView game;

	static inline bool ResizeFrammeBuffer;

private:
	std::vector<ImguiLayer*> ImguiLayers;

	static inline int Newwidht;
	static inline int Newheight;
};

