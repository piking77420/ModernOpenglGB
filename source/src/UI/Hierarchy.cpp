#include "Ui/Hierarchy.hpp"
#include "Ressources/Scene/Scene.h"
#include "LowRenderer/Cam/Camera.h"
#include "App/App.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp" 

void Hierarchy::UpdateLayer(Project& currentProject)
{
	static bool open = true;

	if (!currentProject.currentScene)
		return;


	if (ImGui::Begin("GraphScene", &open))
	{

		std::vector<uint8_t>* transformDataVector = currentProject.currentScene->GetComponentDataArray<Transform>();


		for (size_t i = 0; i < transformDataVector->size() / sizeof(Transform); i++)
		{
			size_t offset = i * sizeof(Transform);
			Transform* transfrom = reinterpret_cast<Transform*>(&(*transformDataVector)[offset]);

			if (!transfrom->Parent)
			{
				ImguiDrawChildren(transfrom->entity, currentProject);

			}
		}

		

		ImGui::End();
	}
}


void Hierarchy::ImguiDrawChildren(Entity* entity, Project& currentProject)
{

	Transform* transform = currentProject.currentScene->GetComponent<Transform>(entity);
	bool hasChildren = !transform->childs.empty();
	static bool open = true;


	ImGuiTreeNodeFlags_ flags;
	if (hasChildren)
	{
		flags = ImGuiTreeNodeFlags_None;
	}
	else
	{
		flags = ImGuiTreeNodeFlags_Leaf;
	}

	ImGui::PushID("");

	if (ImGui::TreeNodeEx(entity->Entityname.c_str(), flags))
	{
		
		if (ImGui::IsItemClicked())
			currentProject.DockingSystem.Insepctor = entity;


		if (hasChildren)
		{
			for (size_t i = 0; i < transform->childs.size(); i++)
			{
				ImguiDrawChildren(transform->childs[i]->entity, currentProject);
			}
		}
		ImGui::TreePop();
	}
	ImGui::PopID();

}


Hierarchy::Hierarchy()
{
	WindowName = "Hierarchy";
}

Hierarchy::~Hierarchy()
{
}
