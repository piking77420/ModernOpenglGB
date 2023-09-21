#include <filesystem>
#include"LowRenderer/Cam/Camera.h"
#include "Core/ECS/Scene/Scene.h"
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

void Scene::RenderScene(Shader& shader)
{
	renderer.RendereScene(this,&shader);
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

	NewEntitie->SetID() = m_registerScene.entities.size();
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
