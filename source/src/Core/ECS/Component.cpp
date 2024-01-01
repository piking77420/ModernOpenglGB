#include "Core/ECS/Component.h"
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "Core/ECS/Scene.h"

void Component::ImguiWindowComponent()
{
	
	if(ImGui::Checkbox("Enable", &isEnable))
	{

	}
	
}
