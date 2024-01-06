#include <filesystem>
#include"LowRenderer/Cam/Camera.h"
#include "Core/ECS/Scene.h"
#include "App/App.h"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "Physics/Transform/Transform.hpp"
#include "Physics/GraphScene/GraphScene.h"
#include "Core/DataStructure/Project.hpp"

void Scene::Init()
{
	for (IEcsSystem* system : m_registerScene.systems)
	{
		system->Init(this);
	}
}

void Scene::Awake()
{
	for (IEcsSystem* system : m_registerScene.systems)
	{
		system->Awake(this);
	}
}

void Scene::Start()
{
	for (IEcsSystem* system : m_registerScene.systems)
	{
		system->Start(this);
	}
}

void Scene::DrawGizmo()
{
	for (IEcsSystem* system : m_registerScene.systems)
	{
		system->OnDrawGizmo(this);
	}
}

void Scene::FixedUpdate()
{
	for (IEcsSystem* system : m_registerScene.systems)
	{
		system->FixedUpdate(this);
	}
}

void Scene::Update()
{
	for (IEcsSystem* system : m_registerScene.systems)
	{
		system->Update(this);
	}
}

void Scene::LateUpdate()
{
	for (IEcsSystem* system : m_registerScene.systems)
	{
		system->LateUpdate(this);
	}
}

void Scene::Render(Shader& shader)
{
	for (IEcsSystem* system : m_registerScene.systems)
	{
		system->Render(shader,this);
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

	NewEntitie->SetID() = (uint32_t)m_registerScene.entities.size();
	NewEntitie->entityName = "Entity " + std::to_string(NewEntitie->ID);
	m_registerScene.entities.push_back(NewEntitie);

	// Minimal Componnent
	AddComponent<Transform>(NewEntitie);

	return NewEntitie;
}

Entity* Scene::GetEntities(uint32_t ID)
{
	return m_registerScene.GetEntiesById(ID);

}

void Scene::OnEntitySelectInspector(uint32_t entityID)
{
	Entity* ent = GetEntities(entityID);


	for (uint32_t i = 0; i < ent->entityComponents.size(); i++)
	{
		if (ent->entityComponents[i] == ComponentNULL) continue;

		if (ImGui::CollapsingHeader(Component::GetComponentName(i).c_str()))
		{

			std::vector<uint8_t>* data = GetComponentDataArray(i);
			Component* comp = reinterpret_cast<Component*>(&data->at(ent->entityComponents[i]));

			comp->ImguiWindowComponent();

		}


	}

	if (ImGui::CollapsingHeader("Add Component"))
	{
		for (uint32_t i = 0; i < Component::GetComponentTypeInfos()->size(); i++)
		{

			if (HasComponent(i, ent))
				continue;

			if (ImGui::Button(Component::GetComponentName(i).c_str()))
			{
				AddComponent(i, ent);
			}

		}


	}



}
