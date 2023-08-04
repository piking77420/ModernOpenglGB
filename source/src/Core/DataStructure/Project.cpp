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

	RendererSystem* rs = new RendererSystem();
	currentScene->AddSystem(rs);
	rs->shaderName = "NormalShader";

	RendererLightSystem* rl = new RendererLightSystem();
	currentScene->AddSystem(rl);
	rl->shaderName = "NormalShader";


	SystemRendererSkyMap* systemRendererSkyMap = new SystemRendererSkyMap();
	currentScene->AddSystem(systemRendererSkyMap);



	Entity* entity = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(entity);
	currentScene->GetComponent<Transform>(entity)->pos += Vector3(2,2,2);
	MeshRenderer* meshRenderer = currentScene->GetComponent<MeshRenderer>(entity);
	meshRenderer->model = ressourcesManager.GetElement<Model>("cube.obj");
	meshRenderer->diffuse = ressourcesManager.GetElement<Texture>("EmerauldBlock.png");
	meshRenderer->specular = ressourcesManager.GetElement<Texture>("EmerauldBlock.png");



	Entity* entityCube2 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(entityCube2);
	currentScene->GetComponent<Transform>(entityCube2)->pos += Vector3(-4, 4, -4);
	currentScene->GetComponent<Transform>(entityCube2)->rotation += Vector3(0.5, 2, -0.8);

	meshRenderer = currentScene->GetComponent<MeshRenderer>(entityCube2);
	meshRenderer->model = ressourcesManager.GetElement<Model>("cube.obj");
	meshRenderer->diffuse = ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	meshRenderer->specular = ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");



	Entity* entity2 = currentScene->CreateEntity();
	currentScene->GetComponent<Transform>(entity2)->scaling = Vector3(0.5, 0.5,0.5);
	currentScene->GetComponent<Transform>(entity2)->pos = Vector3(0, 1000, 0);
	currentScene->AddComponent<DirectionalLight>(entity2);


	GraphScene::BeChildOf(currentScene->GetComponent<Transform>(entityCube2), currentScene->GetComponent<Transform>(entity));

	
	Entity* plane = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(plane);
	MeshRenderer* planerdr = currentScene->GetComponent<MeshRenderer>(plane);
	currentScene->GetComponent<Transform>(plane)->scaling = Vector3(25,0,25);
	planerdr->model = ressourcesManager.GetElement<Model>("plane.obj");
	planerdr->diffuse = ressourcesManager.GetElement<Texture>("woodenGround.jpg");
	planerdr->specular = ressourcesManager.GetElement<Texture>("woodenGround.jpg");

	

	


	currentScene->Init();
}
