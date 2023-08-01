#include <filesystem>
#include"LowRenderer/Cam/Camera.h"
#include "Ressources/Scene/Scene.h"
#include "App/App.h"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"


FrameBuffer* Scene::OpenGlRenderToImgui = new FrameBuffer(windowWidth, windowHeight);
RessourcesManager* Scene::ressourcesManagers = nullptr;

void Scene::Init()
{
	for (IEcsSystem* system : m_register.Systems)
	{
		system->Init(this);
	}
}

void Scene::Awake()
{
	for (IEcsSystem* system : m_register.Systems)
	{
		system->Awake(this);
	}
}

void Scene::Start()
{
	for (IEcsSystem* system : m_register.Systems)
	{
		system->Start(this);
	}
}

void Scene::FixedUpdate()
{
	for (IEcsSystem* system : m_register.Systems)
	{
		system->FixedUpdate(this);
	}
}

void Scene::Update()
{
	for (IEcsSystem* system : m_register.Systems)
	{
		system->Update(this);
	}
}

void Scene::LateUpdate()
{
	for (IEcsSystem* system : m_register.Systems)
	{
		system->LateUpdate(this);
	}
}

void Scene::Render()
{
	for (IEcsSystem* system : m_register.Systems)
	{
		system->Render(this);
	}
}

Scene::Scene(const fs::path& FilePath)
{
	
	cam = Camera::cam;
}


Scene::~Scene()
{


}