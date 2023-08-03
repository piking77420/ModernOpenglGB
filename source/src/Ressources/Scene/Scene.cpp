#include <filesystem>
#include"LowRenderer/Cam/Camera.h"
#include "Ressources/Scene/Scene.h"
#include "App/App.h"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "Physics/Transform/Transform.hpp"
#include "Physics/GraphScene/GraphScene.h"
#include "Core/DataStructure/Project.hpp"


void Scene::Init()
{
	for (IEcsSystem* system : registerScene.Systems)
	{
		system->Init(this);
	}
}

void Scene::Awake()
{
	for (IEcsSystem* system : registerScene.Systems)
	{
		system->Awake(this);
	}
}

void Scene::Start()
{
	for (IEcsSystem* system : registerScene.Systems)
	{
		system->Start(this);
	}
}

void Scene::FixedUpdate()
{
	for (IEcsSystem* system : registerScene.Systems)
	{
		system->FixedUpdate(this);
	}
}

void Scene::Update()
{
	for (IEcsSystem* system : registerScene.Systems)
	{
		system->Update(this);
	}
}

void Scene::LateUpdate()
{
	for (IEcsSystem* system : registerScene.Systems)
	{
		system->LateUpdate(this);
	}
}

void Scene::Render()
{
	for (IEcsSystem* system : registerScene.Systems)
	{
		system->Render(this);
	}
}

Scene::Scene(std::string name)
{
	sceneName = name;
}

Scene::~Scene()
{
}



Entity* Scene::CreateEntity()
{
	Entity* NewEntitie = new Entity();
	NewEntitie->scene = this;

	NewEntitie->SetID() = registerScene.entities.size();
	NewEntitie->Entityname = "Entity " + std::to_string(NewEntitie->ID);
	registerScene.entities.push_back(NewEntitie);

	// Minimal Componnent
	AddComponent<Transform>(NewEntitie);

	return NewEntitie;
}

Entity* Scene::GetEntities(uint32_t ID)
{
	for (size_t i = 0; i < registerScene.entities.size(); i++)
	{
		if (registerScene.entities[i]->GetID() == ID)
			return registerScene.entities[i];
	}

}
