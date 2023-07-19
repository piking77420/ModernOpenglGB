#include <filesystem>
#include"LowRenderer/Cam/Camera.h"
#include <ComponentsBehaviours.h>
#include "Ressources/Scene/Scene.h"
#include "Core/DataStructure/Component/Collider/SphereCollider/SphereCollider.h"
#include "Core/DataStructure/Component/Collider/PlaneCollider.h"
#include "Collider/BoxCollider/BoxCollider.h"
#include "LowRenderer/Ui/UIRenderer.h"
#include "App/App.h"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

FrameBuffer* Scene::OpenGlRenderToImgui = new FrameBuffer(windowWidth, windowHeight);
RessourcesManager* Scene::ressourcesManagers = nullptr;

Scene::Scene(const fs::path& FilePath) 
{
	
	ressourcesManagers = nullptr;
	io = nullptr;
	name = FilePath.filename().generic_string();
	cam = Camera::cam;

}


Scene::~Scene()
{	

	for (size_t i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
	entities.clear();
	LOG("All entites have been deleted",STATELOG::GOOD);
}




void Scene::SceneUpdate(ImGuiIO& _io)
{
	io = &_io;
	Deltatime = io->DeltaTime;

	m_PhysicsEngine.DetermianteCollision(this);

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->PreUpdate(this);
	}

	m_PhysicsEngine.Update(this);

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->FixedUpdate(this);
	}

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(this);
	}
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->LateUpdate(this);
	}
	m_PhysicsEngine.Reset();
	cam->CameraUpdate();
}


void Scene::SaveScene()
{

}

void Scene::Awake()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Awake(this);
	}
}

void Scene::Start()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Start(this);
	}
}

void Scene::AddEntity()
{
	entities.push_back(new Entity());
}

void Scene::RemoveEntity(Entity* entity)
{
}




void Scene::RenderScene(Shader* shaderProgramm, Shader* StencilShader) 
{

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Renderer(this);

		MeshRenderer* meshr = entities[i]->GetComponent<MeshRenderer>();
		Light* l = entities[i]->GetComponent<Light>();
		if (l != nullptr)
		{
			l->SetUniform(shaderProgramm);
		}

		if(meshr != nullptr) 
		{
			meshr->Draw(this, shaderProgramm);
			meshr->MeshRendererDrawStencil(this, StencilShader);

		}
	}
	
}
void Scene::RenderGizmo(Shader* shaderProgramm)
{
	
	for (size_t i = 0; i < entities.size(); i++)
	{
		Collider* c = entities[i]->GetComponent<Collider>();
		
		if(c)
		{
			c->gizmo->Render(shaderProgramm, this);
		}
		
			

	}
	
}
void Scene::RenderUi(Shader* shaderProgramm)
{

	for (size_t i = 0; i < entities.size(); i++)
	{
		UIRenderer* Ui = entities[i]->GetComponent<UIRenderer>();

		if (Ui)
		{
			Ui->Draw(this, shaderProgramm);
		}


	}

}
