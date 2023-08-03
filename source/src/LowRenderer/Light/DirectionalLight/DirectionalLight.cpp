#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"

#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>



void DirectionalLight::ImguiWindowComponent()
{
	ImGui::Text(" ");
	ImGui::ColorPicker4("ambiantColor", lightData.ambiantColor.SetPtr());
	ImGui::ColorPicker4("diffuseLightColor", lightData.diffuseColor.SetPtr());
	ImGui::ColorPicker4("SpecularColor", lightData.specularColor.SetPtr());
	ImGui::DragFloat("SpecularColor", &lightData.SpecularStrengt);

	ImGui::Text(" ");

}

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::~DirectionalLight()
{
}