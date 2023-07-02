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

Scene::Scene(std::string _filepath)
{
	
	ressourcesManagers = nullptr;
	io = nullptr;
	name = RessourcesManager::GetRessourcesName(_filepath);
	cam = Camera::cam;

}

Scene::Scene()
{	
	ressourcesManagers = nullptr;
	io = nullptr;
	cam = Camera::cam;

}

Scene::~Scene()
{	

	for (size_t i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
	entities.clear();
	Debug::Log->LogGood("All entites have been deleted");
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

	FixedUpdate();
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
void Scene::FixedUpdate()
{
	//m_PhysicsEngine.UpdateColliders()
	/*
	for (size_t i = 0; i < entities.size(); i++)
	{
		/*
		Collider* c = entities[i]->GetComponent<Collider>();

		if (c != nullptr)
		{
			for (size_t i = 0; i < c->CollisionShape.size(); i++)
			{
				c->CollisionShape[i]->Update(*c);
			}
		}

		
	}*/

	m_PhysicsEngine.Update(this);
	//;
}
