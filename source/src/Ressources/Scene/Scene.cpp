#include <filesystem>
#include <ComponentsBehaviours.h>
#include "Ressources/Scene/Scene.h"
#include "Core/DataStructure/Component/Collider/SphereCollider/SphereCollider.h"
#include "Core/DataStructure/Component/Collider/PlaneCollider.h"
#include "Collider/BoxCollider/BoxCollider.h"
#include "LowRenderer/Ui/UIRenderer.h"



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


	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->PreUpdate(this);
	}

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(this);
	}
	float time = (float)glfwGetTime();
	
	cam->CameraUpdate();
}
void Scene::LateUpdate()
{

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->LateUpdate(this);
	}


}

void Scene::Saving()
{
	
	
}

IResource* Scene::Load(std::string path)
{
	pathLocation = path;



	return nullptr;
}


void Scene::RenderScene(Shader* shaderProgramm, Shader* StencilShader) 
{

	for (size_t i = 0; i < entities.size(); i++)
	{
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
		
		if (c != nullptr && c->Gizmorenderer != nullptr)
			c->Gizmorenderer->Draw(this, shaderProgramm);


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
void Scene::PhyscisUpdate()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		Collider* c = entities[i]->GetComponent<Collider>();

		if (c != nullptr)
		{
			for (size_t i = 0; i < c->CollisionShape.size(); i++)
			{
				c->CollisionShape[i]->Update(*c);
			}
		}


	}


	m_PhysicsEngine.UpdateColliders();
}
