#include <Core/DataStructure/Entity/Entity.h>
#include<Core/Debug/Imgui/imgui.h>
#include "App/App.h"
#include "Ressources/Scene/Scene.h"

#include "Physics/Transform/Transform.h"



void Entity::PreUpdate(Scene* scene)
{
	for (Component* c : Components)
	{
		c->PreUpdate(scene);
	}
}


void Entity::Update(Scene* scene)
{
	for(Component* c : Components)
	{
		c->Update(scene);
	}
}

void Entity::Renderer(Scene* scene)
{
	for (Component* c : Components)
	{
		c->Renderer(scene);
	}
}

void Entity::FixedUpdate(Scene* scene)
{
	for (Component* c : Components)
	{
		c->FixedUpdate(scene);
	}
}

void Entity::LateUpdate(Scene* scene)
{
	for (Component* c : Components)
	{
		c->LateUpdate(scene);
	}
}

void Entity::ImguiEntityWindow()
{


}

bool Entity::HasParent()
{
	if(transform.Parents != nullptr)
	{
		return true;
	}
	return false;
}

void Entity::OnSelected()
{
	ImGui::PushID(name.c_str());

	ImGui::CollapsingHeader(name.c_str(), NULL, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf);


	for (Component* c : Components)
	{

		c->ImguiWindow();
		ImGui::Text("");

	}
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Button Text").x) * 0.5f);

	if (ImGui::Button("AddComponent"))
	{
		if (ImGui::Button("MeshRenderer"))
		{
			AddComponent<MeshRenderer>();
		}

	}


	ImGui::PopID();
}







Entity::Entity(std::string _name,Scene* _scene) : name(_name) , transform(Transform(*this))
{
	this->AddComponent<Transform>(&transform);
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;
}

Entity::Entity(std::string _name, Transform _transform) :   name(_name), transform(_transform)
{
	this->AddComponent<Transform>(&transform);
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;
}

Entity::Entity() :  transform(Transform(*this))
{
	this->AddComponent<Transform>(&transform);
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;

	this->name = "Entity " + std::to_string(m_ID);
}


Entity::~Entity()
{
	unsigned int nbrOfComponents = 0;
	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i] = nullptr;
		delete Components[i];
		if(Components[i] == nullptr)
		{
			nbrOfComponents++;
		}
	}
	if (nbrOfComponents == Components.size())
	{
		Debug::Log->LogGood("All components of " + name + " has been free");
	}
	else
	{
		Debug::Log->LogWarning("All components of " + name + " has not been free");
	}

	Components.clear();
}




