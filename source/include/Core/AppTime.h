#pragma once
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>

static class AppTime
{
public:
	
	static inline float GetDeltatime()
	{
		return ImGui::GetIO().DeltaTime;
	}

	constexpr static inline float GetFixedDeltatime()
	{
		return 0.03f;
	}


};

