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

void Component::Awake(Scene* scene)
{
}

void Component::Start(Scene* scene)
{
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

void Component::FixedUpdate(Scene* scene)
{
}



Component::Component() 
{
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;

}

Component::Component(Entity* entity)
{
	EntityAttachTo = entity;
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;
}



