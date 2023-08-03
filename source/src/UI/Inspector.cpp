#include "UI/Inspector.hpp"
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "App/App.h"

void Inspector::UpdateLayer(Project& currentProject)
{
	if (ImGui::Begin(WindowName.c_str()))
	{


		ImGui::PushID("");
		
		if (currentProject.DockingSystem.Insepctor)
			currentProject.DockingSystem.Insepctor->OnInspector();
	

		ImGui::PopID();



		ImGui::End();
	}

}
