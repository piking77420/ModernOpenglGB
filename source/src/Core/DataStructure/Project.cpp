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
FrameBuffer* Project::OpenGlRenderToImgui = new FrameBuffer(800, 800);

void Project::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (!OpenGlRenderToImgui)
		return;
	glViewport(0, 0, width, height);
	OpenGlRenderToImgui->ResizeFrammeBuffer(width, height);
}



void Project::Update()
{

	Shader* shaderNormal = ressourcesManager.GetElement<Shader>("NormalShader");
	Shader* shaderShadowMapping = ressourcesManager.GetElement<Shader>("ShadowMapping");

	Shader* skybox = ressourcesManager.GetElement<Shader>("SkyBoxShader");

	mainCamera->SetCameraInfoForShaders(ressourcesManager);
	mainCamera->CameraUpdate();




	OpenGlRenderToImgui->Bind();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	currentScene->FixedUpdate();
	currentScene->Update();
	currentScene->LateUpdate();


	currentScene->DrawGizmo();

	currentScene->Render(*shaderShadowMapping);
	currentScene->RenderScene(*shaderShadowMapping);
	
	OpenGlRenderToImgui->UnBind();

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
	

	RendererShadowSystem* rShadow = new RendererShadowSystem();
	currentScene->AddSystem(rShadow);

	RendererLightSystem* rl = new RendererLightSystem();
	currentScene->AddSystem(rl);
	

	ColliderSystem* colliderSystem = new ColliderSystem();
	currentScene->AddSystem(colliderSystem);

	PhysicsSystem* physicsSystem = new PhysicsSystem();
	currentScene->AddSystem(physicsSystem);


	SystemRendererSkyMap* systemRendererSkyMap = new SystemRendererSkyMap();
	currentScene->AddSystem(systemRendererSkyMap);

	


	
	Entity* plane = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(plane);

	MeshRenderer* planerdr = currentScene->GetComponent<MeshRenderer>(plane);
	currentScene->GetComponent<Transform>(plane)->scaling = Vector3(25, 0.1, 25);
	currentScene->GetComponent<Transform>(plane)->pos = Vector3(0, -0.5f, 0);

	planerdr->mesh = ressourcesManager.GetElement<Mesh>("cube.obj");
	planerdr->material.diffuse = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	planerdr->material.specular = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");



	Entity* entity1 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(entity1);
	currentScene->GetComponent<Transform>(entity1)->pos += Vector3(2.0f, 0.0f, 1.0);
	currentScene->GetComponent<Transform>(entity1)->scaling = Vector3(0.5, 0.5, 0.5);
	MeshRenderer* meshRenderer = currentScene->GetComponent<MeshRenderer>(entity1);
	meshRenderer->mesh = ressourcesManager.GetElement<Mesh>("cube.obj");
	meshRenderer->material.diffuse = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	meshRenderer->material.specular = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	currentScene->AddComponent<PointLight>(entity1);




	Entity* entity2 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(entity2);
	currentScene->GetComponent<Transform>(entity2)->pos += Vector3(0.0f, 1.5f, 0.0);
	MeshRenderer* meshRenderer2 = currentScene->GetComponent<MeshRenderer>(entity2);
	meshRenderer2->mesh = ressourcesManager.GetElement<Mesh>("cube.obj");
	meshRenderer2->material.diffuse = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	meshRenderer2->material.specular = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");



	Entity* entity3 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(entity3);
	currentScene->GetComponent<Transform>(entity3)->pos += Vector3(-1.0f, 0.0f, 2.0);
	currentScene->GetComponent<Transform>(entity3)->rotation = Vector3(Math::DegreesToRadians(60), 0, Math::DegreesToRadians(60));
	currentScene->GetComponent<Transform>(entity3)->scaling = Vector3(0.25, 0.25, 0.25);

	MeshRenderer* meshRenderer3 = currentScene->GetComponent<MeshRenderer>(entity3);
	meshRenderer3->mesh = ressourcesManager.GetElement<Mesh>("cube.obj");
	meshRenderer3->material.diffuse = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	meshRenderer3->material.specular = *ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");



	/*
	Entity* entityCube2 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(entityCube2);
	currentScene->AddComponent<BoxCollider>(entityCube2);
	currentScene->AddComponent<Rigidbody>(entityCube2);
	currentScene->GetComponent<Transform>(entityCube2)->pos += Vector3(-4, 10 , -4);
	MeshRenderer* meshRenderer2 = currentScene->GetComponent<MeshRenderer>(entityCube2);
	meshRenderer2->model = ressourcesManager.GetElement<Model>("cube.obj");
	meshRenderer2->diffuse = ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	meshRenderer2->specular = ressourcesManager.GetElement<Texture>("DiamondBlock.jpg");
	
	*/
	
	Entity* Directionnale = currentScene->CreateEntity();
	currentScene->GetComponent<Transform>(Directionnale)->pos = Vector3(-2.0f, 4.0f, -1.0f);
	currentScene->AddComponent<DirectionalLight>(Directionnale);



	

	


	currentScene->Init();
	OpenGlRenderToImgui->Init();

}
