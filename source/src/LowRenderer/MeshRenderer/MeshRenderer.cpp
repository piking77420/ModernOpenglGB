#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>
#include "Ressources/Model/Model.h"

void MeshRenderer::ImguiWindowComponent()
{

	ImGui::Text("MeshRenderer");

	ImGui::PushID("");

	ImGui::Text("Material \n");

	ImGui::Text("Diffuse"); ImGui::SameLine();
	ImGui::Image((ImTextureID)material.diffuse.ID,ImVec2(50,50),
		ImVec2(0, 1),
		ImVec2(1, 0));


	ImGui::DragFloat("shininess", &material.shininess);
	ImGui::DragFloat("ka", &material.ka,0.15f,0,1);
	ImGui::DragFloat("kd", &material.kd, 0.15f,0,1);
	ImGui::DragFloat("ks", &material.ks, 0.15f,0,1);

	ImGui::PopID();

}
