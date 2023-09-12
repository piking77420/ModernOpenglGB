#include "Core/DataStructure/Project.hpp"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "UI/DockingSystem.hpp"
 #include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "UI/ContentBrowser.h"
#include "LowRenderer/Gizmo/Gizmo.hpp"

#include "LowRenderer/MeshRenderer/MeshRenderer.h"
#include "Physics/Collider/ColliderSystem.hpp"

#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/RendererLightSystem/RendererLightSystem.hpp"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/SystemRendererSkyMap/SystemRendererSkyMap.hpp"
#include "LowRenderer/RendererShadowSystem/RendererShadowSystem.h"
#include "LowRenderer/Gizmo/Gizmo.hpp"
#include "LowRenderer/Renderer/Renderer.hpp"
#include "Physics/Collider/SphereCollider.hpp"
#include "Physics/GraphScene/GraphScene.h"
#include "Physics/Collider/BoxCollider.hpp"
#include "Physics/PhysicsSystem/PhysicsSystem.hpp"
#include "Physics/RigidBody/Rigidbody.h"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "../../../ProjectFolder/Project1/assets/Scipt/RumicsCube.h"
#include "Core/ThreadPool/ThreadPool.h"




void Project::Update()
{

	Shader* shaderNormal = ressourcesManager.GetElement<Shader>("NormalShader");
	Shader* shaderShadowMapping = ressourcesManager.GetElement<Shader>("ShadowMapping");

	Shader* skybox = ressourcesManager.GetElement<Shader>("SkyBoxShader");

	mainCamera->SetCameraInfoForShaders(ressourcesManager);
	mainCamera->CameraUpdate();




	currentScene->renderer.OpenGlRenderToImgui->Bind();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);



	currentScene->FixedUpdate();
	currentScene->Update();
	currentScene->LateUpdate();

	currentScene->Render(*shaderShadowMapping);
	currentScene->RenderScene(*shaderShadowMapping);
	currentScene->DrawGizmo();

	currentScene->renderer.OpenGlRenderToImgui->UnBind();

	DockingSystem.UpdateDockSpace(*this);

}

Project::Project(std::string ProjectPath) 
{
	ressourcesManager.LoadAllAssets(ProjectPath);
	
	currentScene = new Scene("Scene 0");
	currentScene->currentproject = this;
	mainCamera = Camera::cam;




	
	ContentBrowser::BasePath = ProjectPath;
	ContentBrowser::CurrentPath = ContentBrowser::BasePath;
	Gizmo::InitGizmo(*this);
	InitScene();

}

Project::Project() 
{
	ressourcesManager.LoadAllAssets("ProjectFolder/Project1");
	currentScene = new Scene("Scene 0");
	currentScene->currentproject = this;
	mainCamera = Camera::cam;

	
	ContentBrowser::BasePath = "ProjectFolder/Project1";
	ContentBrowser::CurrentPath = ContentBrowser::BasePath;
	Gizmo::InitGizmo(*this);
	InitScene();

}

Project::~Project()
{
}











void Project::InitScene()
{
	
	// UPDATE PHYSICS FIRST
	currentScene->AddSystem(new PhysicsSystem());
	// Check Collsiion for nextframe
	currentScene->AddSystem(new ColliderSystem());
	// UPDATE MATRIX 
	currentScene->AddSystem(new GraphScene());



	currentScene->AddSystem(new RendererShadowSystem());
	currentScene->AddSystem(new RendererLightSystem());
	currentScene->AddSystem(new SystemRendererSkyMap());

	
	currentScene->AddSystem(new RumicsCube());
	/*
	
	Entity* plane = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(plane);
	MeshRenderer* planerdr = currentScene->GetComponent<MeshRenderer>(plane);
	currentScene->GetComponent<Transform>(plane)->scaling = Vector3(25, 0.1, 25);
	currentScene->GetComponent<Transform>(plane)->pos = Vector3(0, -0.5f, 0);
	planerdr->mesh = *ressourcesManager.GetElement<Mesh>("cube.obj");
	planerdr->material.diffuse = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	planerdr->material.specular = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");


	*/




	//currentScene->AddComponent<Rigidbody>(entity2);

	
	Entity* Directionnale = currentScene->CreateEntity();
	currentScene->GetComponent<Transform>(Directionnale)->pos = Vector3(-2.0f, 4.0f, -1.0f);
	currentScene->AddComponent<DirectionalLight>(Directionnale);


	Entity* Cube1 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(Cube1);

	currentScene->GetComponent<Transform>(Cube1)->pos = Vector3(-2.0f, 4.0f, -1.0f);
	MeshRenderer* Cube1rdr = currentScene->GetComponent<MeshRenderer>(Cube1);
	currentScene->AddComponent<BoxCollider>(Cube1);
	Cube1rdr->mesh = *ressourcesManager.GetElement<Mesh>("cube.obj");
	Cube1rdr->material.diffuse = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	Cube1rdr->material.specular = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");

	Entity* Cube2 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(Cube2);
	currentScene->AddComponent<BoxCollider>(Cube2);
	currentScene->GetComponent<Transform>(Cube2)->pos = Vector3(-4.0f, 5.0f, -3.0f);

	currentScene->GetComponent<Transform>(Cube2)->pos = Vector3(-2.0f, 4.0f, -1.0f);
	MeshRenderer* Cube2rdr = currentScene->GetComponent<MeshRenderer>(Cube2);
	Cube2rdr->mesh = *ressourcesManager.GetElement<Mesh>("cube.obj");
	Cube2rdr->material.diffuse = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	Cube2rdr->material.specular = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");

	


	currentScene->Init();
	currentScene->renderer.OpenGlRenderToImgui->Init();

}
