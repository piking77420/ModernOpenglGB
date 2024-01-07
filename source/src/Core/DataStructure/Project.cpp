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

#include"App/App.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "AppTime.h"

void Project::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	m_Width = width;
	m_Height = height;
	Resize = true;
}



void Project::Update()
{
	dockingSystem.BindDockSpace();


	if(Resize)
	{
		dockingSystem.scene.ResizeBuffer((float)m_Width, (float)m_Height);
		dockingSystem.game.ResizeBuffer((float)m_Width, (float)m_Height);

		Resize = false;
	}



	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	AppTime::GetDeltatimeFromImgui() = ImGui::GetIO().DeltaTime;
	coreInput.LookForInput();

	// ORDER INPORTENT Input are made here so don't put it after update matrix made in fixedUpdate;
	dockingSystem.UpdateDockSpace(*this);

	currentScene->FixedUpdate();
	currentScene->Update();
	currentScene->LateUpdate();


	Render(&dockingSystem.scene);
	Render(&dockingSystem.game);
	dockingSystem.RenderDockSpace(*this);

	dockingSystem.UnBindDockSpace();

	coreInput.ClearInputs();
}

void Project::Render(SceneView* sceneView)
{
	sceneView->BindSceneView();

	Renderer::BindedFrameBuffer->Bind();
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	

	ResourcesManager::SetCameraInfoForShader(&sceneView->m_cam);


	currentScene->Render();
	Renderer::RendereScene(currentScene);
	currentScene->DrawGizmo();

	Renderer::BindedFrameBuffer->UnBind();

	// Make the effect here // 



}



Project::Project() 
{




	ResourcesManager::LoadAllAssets("ProjectFolder/Project1");
	currentScene = new Scene("Scene 0");
	currentScene->currentProject = this;

	
	ContentBrowser::BasePath = "ProjectFolder/Project1";
	ContentBrowser::CurrentPath = ContentBrowser::BasePath;
	Gizmo::InitGizmo(*this);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	InitScene();


}

Project::~Project()
{
	ResourcesManager::DeleteAllasset();
	delete currentScene;
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
	//currentScene->AddSystem(new RendererLightSystem());
	currentScene->AddSystem(new SystemRendererSkyMap());

	
	Entity* Directionnale = currentScene->CreateEntity();
	currentScene->GetComponent<Transform>(Directionnale)->pos = Vector3(-2.0f, 7, -1.0f);
	currentScene->AddComponent<DirectionalLight>(Directionnale);
	Directionnale->entityName = "DirectionalLight";
	
	
	Entity* pointLight = currentScene->CreateEntity();
	currentScene->GetComponent<Transform>(pointLight)->pos = Vector3(2.0f, 4, 1.0f);
	currentScene->AddComponent<PointLight>(pointLight);
	pointLight->entityName = "PointLight";

	Entity* ground = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(ground);
	currentScene->GetComponent<Transform>(ground)->scaling = Vector3(10, 1, 10);
	ground->entityName = "Ground";
	MeshRenderer* meshRenderer = currentScene->GetComponent<MeshRenderer>(ground);
	meshRenderer->mesh = *ResourcesManager::GetElement<Mesh>("cube.obj");
	//PHONG // 
	meshRenderer->material.phongMaterial.albedo = *ResourcesManager::GetElement<Texture>("woodenGround.jpg");
	meshRenderer->material.phongMaterial.ka = 0.005f;
	meshRenderer->material.phongMaterial.kd = 0.3f;
	meshRenderer->material.phongMaterial.ks = 0.2f;
	meshRenderer->material.phongMaterial.shininess = 10.f;
	
	// PBR // 
	meshRenderer->material.pbrMaterial.albedo.ressourceMap = ResourcesManager::GetElement<Texture>("wood_0066_color_2k.jpg");
	meshRenderer->material.pbrMaterial.metallic.coeff = 0;
	meshRenderer->material.pbrMaterial.roughness.ressourceMap = ResourcesManager::GetElement<Texture>("wood_0066_roughness_2k.jpg");
	meshRenderer->material.pbrMaterial.ao.ressourceMap = ResourcesManager::GetElement<Texture>("wood_0066_ao_2k.jpg");






	Entity* Cube = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(Cube);
	currentScene->GetComponent<Transform>(Cube)->pos = Vector3(0, 2.5, 0);


	MeshRenderer* meshRendererCube = currentScene->GetComponent<MeshRenderer>(Cube);
	meshRendererCube->mesh = *ResourcesManager::GetElement<Mesh>("Sphere.obj");
	// Phong
	meshRendererCube->material.phongMaterial.albedo = *ResourcesManager::GetElement<Texture>("EmerauldBlock.png");
	meshRendererCube->material.phongMaterial.ka = 0.005f;
	meshRendererCube->material.phongMaterial.kd = 0.7;
	meshRendererCube->material.phongMaterial.ks = 0.75;
	meshRendererCube->material.phongMaterial.shininess = 80;
	/*
	// PBR
	meshRendererCube->material.pbrMaterial.albedo.ressourceMap = resourcesManager.GetElement<Texture>("plasticpattern1-albedo.png");
	meshRendererCube->material.pbrMaterial.metallic.ressourceMap = resourcesManager.GetElement<Texture>("plasticpattern1-metalness.png");
	meshRendererCube->material.pbrMaterial.roughness.ressourceMap = resourcesManager.GetElement<Texture>("plasticpattern1-roughness2.png");
	*/

	meshRendererCube->material.pbrMaterial.albedo.coeff = Vector3(1, 0, 0);
	meshRendererCube->material.pbrMaterial.metallic.coeff = 0.4;
	meshRendererCube->material.pbrMaterial.roughness.coeff = 0.1;

	currentScene->Init();

}
