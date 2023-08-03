#include "Core/DataStructure/Project.hpp"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "UI/DockingSystem.hpp"
 #include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "UI/ContentBrowser.h"

#include "LowRenderer/RendererSystem/RendererSystem.hpp"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"

#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/RendererLightSystem/RendererLightSystem.hpp"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/SystemRendererSkyMap/SystemRendererSkyMap.hpp"

#include "LowRenderer/Renderer/Renderer.hpp"

#include "Physics/GraphScene/GraphScene.h"



void Project::Update()
{
	m_io = ImGui::GetIO();

	mainCamera->SetCameraInfoForShaders(ressourcesManager);
	mainCamera->CameraUpdate();



	renderer.PreRendererScene(currentScene);

	currentScene->FixedUpdate();
	currentScene->Update();
	currentScene->LateUpdate();

	currentScene->Render();
	renderer.RendereScene(currentScene);


	DockingSystem.UpdateDockSpace(*this);

}

Project::Project(std::string ProjectPath) : m_io(ImGui::GetIO())
{
	ressourcesManager.LoadAllAssets(ProjectPath);
	
	currentScene = new Scene("Scene 0");
	currentScene->currentproject = this;
	mainCamera = Camera::cam;





	ContentBrowser::BasePath = ProjectPath;
	ContentBrowser::CurrentPath = ContentBrowser::BasePath;

	InitScene();

}

Project::Project() : m_io(ImGui::GetIO())
{
	ressourcesManager.LoadAllAssets("ProjectFolder/Project1");
	currentScene = new Scene("Scene 0");
	currentScene->currentproject = this;
	mainCamera = Camera::cam;


	ContentBrowser::BasePath = "ProjectFolder/Project1";
	ContentBrowser::CurrentPath = ContentBrowser::BasePath;
	InitScene();

}

Project::~Project()
{
}

void Project::InitScene()
{

	currentScene->AddSystem<RendererSystem>();
	RendererSystem* rs = currentScene->GetSystem<RendererSystem>();
	rs->shaderName = "NormalShader";

	currentScene->AddSystem<RendererLightSystem>();
	RendererLightSystem* rl = currentScene->GetSystem<RendererLightSystem>();
	rl->shaderName = "NormalShader";


	currentScene->AddSystem<SystemRendererSkyMap>();
	SystemRendererSkyMap* systemRendererSkyMap = currentScene->GetSystem<SystemRendererSkyMap>();



	Entity* entity = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(entity);
	currentScene->GetComponent<Transform>(entity)->pos += Vector3(2,2,2);




	MeshRenderer* meshRenderer = currentScene->GetComponent<MeshRenderer>(entity);
	meshRenderer->model = ressourcesManager.GetElement<Model>("viking_room.obj");
	meshRenderer->diffuse = ressourcesManager.GetElement<Texture>("EmerauldBlock.png");
	meshRenderer->specular = ressourcesManager.GetElement<Texture>("EmerauldBlock.png");



	Entity* entity2 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(entity2);
	MeshRenderer* meshRenderer2 = currentScene->GetComponent<MeshRenderer>(entity2);
	meshRenderer2->model =  ressourcesManager.GetElement<Model>("Sphere.obj");
	meshRenderer2->diffuse = ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	meshRenderer2->specular = ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");

	currentScene->AddComponent<DirectionalLight>(entity2);


	GraphScene::BeChildOf(currentScene->GetComponent<Transform>(entity2), currentScene->GetComponent<Transform>(entity));
	


	currentScene->Init();
}
