#include "Ui/Hierarchy.hpp"
#include "ECS/Scene.h"
#include "LowRenderer/Cam/Camera.h"
#include "App/App.h"
#include "Physics/Transform/Transform.hpp"
#include "Core/DataStructure/Project.hpp" 

void Hierarchy::UpdateLayer(Project& currentProject)
{

	static bool open = true;

	if (!currentProject.currentScene)
		return;



	ImGui::Begin("GraphScene", &open);
	
	IsFocus = ImGui::IsWindowFocused();



		std::vector<Transform>* transformDataVector = currentProject.currentScene->GetComponentDataArray<Transform>();


		for (size_t i = 0; i < transformDataVector->size() ; i++)
		{
			Transform* transfrom = &(*transformDataVector)[i];

			if (!transfrom->parent)
			{
				Entity* entity = currentProject.currentScene->GetEntities(transfrom->entityID);
				ImguiDrawChildren(entity, currentProject);

			}
		}

		

	ImGui::End();
	


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

	if (ImGui::TreeNodeEx(entity->entityName.c_str(), flags))
	{
		
		if (ImGui::IsItemClicked())
		{
			currentProject.dockingSystem.EnitySelectedID = entity->ID;
		}


		if (hasChildren)
		{
			for (size_t i = 0; i < transform->childs.size(); i++)
			{
				Entity* entity = currentProject.currentScene->GetEntities(transform->childs[i].second->entityID);
				ImguiDrawChildren(entity, currentProject);
			}
		}
		ImGui::TreePop();
	}
	ImGui::PopID();

}

void Hierarchy::HierarchyMenue(Project& currentProject)
{
	

	ImGui::SetNextWindowPos(ImGui::GetMousePos(), 0, ImVec2(0, 0));


	if (ImGui::BeginChild("HierarchyMenu"))
	{
		if (ImGui::MenuItem("Add Entity"))
		{
			currentProject.currentScene->CreateEntity();
		}

		ImGui::EndChild();
	}

}


Hierarchy::Hierarchy()
{
	WindowName = "Hierarchy";
}

Hierarchy::~Hierarchy()
{
}

