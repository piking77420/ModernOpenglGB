#include <Core/DataStructure/Component/Component.h>
#include <Core/DataStructure/Entity/Entity.h>
#include"App/App.h"
#include "Ressources/Scene/Scene.h"

void Component::ImguiWindowComponents()
{
}

void Component::ImguiWindow()
{
	ImGui::PushID(m_ID);

	if(ImGui::TreeNode(m_ComponentName.c_str()))
	{

		ImGui::Checkbox("Enable", &IsEnabled);
		this->ImguiWindowComponents();
		ImGui::TreePop();
		ImGui::Spacing();
	
	}
	ImGui::PopID();

}

void Component::PreUpdate(Scene* scene)
{
}




void Component::Update(Scene* scene)
{
}

void Component::LateUpdate(Scene* scene)
{
}

Component::Component() 
{
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;

}

void* Component::operator new(size_t size)
{
	
	return malloc(size);
}


