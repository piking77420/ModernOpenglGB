#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>

#include "UI/DockingSystem.hpp"
#include "Core/DataStructure/Project.hpp"
#include "Ressources/Scene/Scene.h"
#include "LowRenderer/Cam/Camera.h"
#include "UI/ContentBrowser.h"
#include "UI/Inspector.hpp"
#include "UI/Log.hpp"
#include "UI/Hierarchy.hpp"

void DockingSystem::UpdateDockSpace(Project& CurrentProject)
{
	// Create docking layout
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
	if (opt_fullscreen)
		dockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
	}

	// Begin docking layout
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);
	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	ImGuiID dockspaceID = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

	/*
	// Create windows
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open")) {}
			if (ImGui::MenuItem("Save")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	*/

	for (ImguiLayer* imguiLayer : ImguiLayers)
	{
		imguiLayer->UpdateLayer(CurrentProject);
	}



	ImGui::End();
	
}

DockingSystem::DockingSystem()
{
	ImguiLayers.push_back(new ContentBrowser());
	ImguiLayers.push_back(new Hierarchy());
	ImguiLayers.push_back(new Inspector());
	ImguiLayers.push_back(new Log());


}
