#include "UI/Inspector.hpp"
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "App/App.h"
#include "Core/ECS/Entity.h"


void Inspector::UpdateLayer(Project& currentProject, std::vector<InputEvent*>& inputsEvents)
{
	if (ImGui::Begin(WindowName.c_str()))
	{


		ImGui::PushID("");
		
		if (currentProject.dockingSystem.EnitySelectedID != EntityNULL)
			currentProject.currentScene->OnEntitySelectInspector(currentProject.dockingSystem.EnitySelectedID);
	

		ImGui::PopID();



		ImGui::End();
	}

}

void Inspector::ListenToInput(Project& currentProject,std::vector<InputEvent*>& inputEvent)
{
}
