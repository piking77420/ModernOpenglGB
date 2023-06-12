#include <Core/DataStructure/Entity/Entity.h>
#include<Core/Debug/Imgui/imgui.h>

#include "Physics/Transform/Transform.h"

uint32_t Entity::GloblalIDs = 0;


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

void Entity::LateUpdate(Scene* scene)
{
	for (Component* c : Components)
	{
		c->LateUpdate(scene);
	}
}

void Entity::ImguiEntityWindow()
{
	ImGui::PushID(name.c_str());

	if (ImGui::CollapsingHeader(name.c_str()))
	{	
		for (Component* c : Components)
		{

			c->ImguiWindow();
			ImGui::Text("");

		}

		
	}
	ImGui::PopID();

}

bool Entity::HasParent()
{
	if(transform.Parents != nullptr)
	{
		return true;
	}
	return false;
}




Entity::Entity(std::string _name,Scene* _scene) : name(_name) , transform(Transform(*this))
{
	scene = _scene;
	this->AddComponent<Transform>(&transform);
	this->ID = GloblalIDs;
	GloblalIDs++;
}

Entity::Entity(std::string _name, Transform _transform) :   name(_name), transform(_transform)
{
	this->ID = GloblalIDs;
	GloblalIDs++;
}

Entity::Entity() :  transform(Transform(*this))
{

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




