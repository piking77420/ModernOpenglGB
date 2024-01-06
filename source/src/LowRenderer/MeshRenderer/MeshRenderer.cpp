#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>
#include "Ressources/Model/Model.h"
#include "Project.hpp"

void MeshRenderer::ImguiWindowComponent()
{

	ImGui::Text("MeshRenderer");



	if(Project::shaderType == MATERIALSHADER::PHONG)
	{
		ImGui::PushID("");

		ImGui::Text("Material PHONG \n");

		ImGui::Text("Diffuse"); ImGui::SameLine();
		ImGui::Image((ImTextureID)material.phongMaterial.albedo.ID, ImVec2(50, 50),
			ImVec2(0, 1),
			ImVec2(1, 0));


		ImGui::DragFloat("shininess", &material.phongMaterial.shininess);
		ImGui::DragFloat("ka", &material.phongMaterial.ka, 0.15f, 0, 1);
		ImGui::DragFloat("kd", &material.phongMaterial.kd, 0.15f, 0, 1);
		ImGui::DragFloat("ks", &material.phongMaterial.ks, 0.15f, 0, 1);

		ImGui::PopID();
	}
	else
	{



		ImGui::PushID("");

		ImGui::Text("MaterialPBR \n");

		ImGuiColorEditFlags_ flags = ImGuiColorEditFlags_PickerHueWheel ;
		flags << ImGuiColorEditFlags_HDR;

		ImGui::Text("Albedo");
		if(material.pbrMaterial.albedo.ressourceMap!= nullptr)
		{
			ImGui::Image((ImTextureID)material.pbrMaterial.albedo.ressourceMap->ID, ImVec2(50, 50),
				ImVec2(0, 1),
				ImVec2(1, 0));
		}
		else
		{
			ImGui::ColorPicker3("Albedo", material.pbrMaterial.albedo.coeff.SetPtr(), flags);
		}
	

		ImGui::Text("Metallic");
		if (material.pbrMaterial.metallic.ressourceMap != nullptr)
		{
			ImGui::Image((ImTextureID)material.pbrMaterial.metallic.ressourceMap->ID, ImVec2(50, 50),
				ImVec2(0, 1),
				ImVec2(1, 0));
		}
		else
		{
			ImGui::SliderFloat("Metallic", &material.pbrMaterial.metallic.coeff,0,1);
		}

		ImGui::Text("Rougness");
		if (material.pbrMaterial.roughness.ressourceMap != nullptr)
		{
			ImGui::Image((ImTextureID)material.pbrMaterial.roughness.ressourceMap->ID, ImVec2(50, 50),
				ImVec2(0, 1),
				ImVec2(1, 0));
		}
		else
		{
			ImGui::SliderFloat("Rougness", &material.pbrMaterial.roughness.coeff, 0, 1);
		}

		ImGui::Text("Occlusion");
		if (material.pbrMaterial.roughness.ressourceMap != nullptr)
		{
			ImGui::Image((ImTextureID)material.pbrMaterial.ao.ressourceMap->ID, ImVec2(50, 50),
				ImVec2(0, 1),
				ImVec2(1, 0));
		}
		else
		{
			ImGui::SliderFloat("Occlusion", &material.pbrMaterial.ao.coeff, 0, 1);
		}


		ImGui::PopID();


	}



}
