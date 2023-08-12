#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"

#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>



void DirectionalLight::ImguiWindowComponent()
{
	ImGui::Text(" ");
	ImGui::ColorPicker4("ambiantColor", lightData.color.SetPtr());
	ImGui::DragFloat("minimumRange", &lightData.minimumRange);
	ImGui::DragFloat("maxRange", &lightData.maxRange);
	ImGui::DragFloat("Size", &lightData.size);
	ImGui::Text(" ");

}

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::~DirectionalLight()
{
}