#include "LowRenderer/MeshRenderer/MeshRenderer.h"

#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>
#include "Ressources/Model/Model.h"

void MeshRenderer::ImguiWindowComponent()
{
	ImGui::Text("MeshRenderer");

	ImGui::PushID("");

	ImGui::Text(model->name.c_str());
	ImGui::Text("Material");
	ImGui::DragInt("diffuse", &material.diffuse);
	ImGui::DragInt("diffuse", &material.specular);
	ImGui::DragFloat("diffuse", &material.shininess);

	ImGui::PopID();

}
