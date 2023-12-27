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





void Project::Update()
{
	std::vector<InputEvent*> inputsEvents;

	shaderShadowMapping = resourcesManager.GetElement<Shader>("ShadowMapping");


	resourcesManager.SetCameraInfoForShader(mainCamera);
	mainCamera->CameraUpdate();



	currentScene->renderer.OpenGlRenderToImgui->Bind();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	coreInput.LookForInput(inputsEvents);
	currentScene->FixedUpdate();
	float value = (float)std::sin(ImGui::GetTime());
	currentScene->GetComponent<Transform>(currentScene->GetEntities(2))->rotationValue += Vector3(value, value, 0) * 0.16;

	currentScene->Update();
	currentScene->LateUpdate();



	currentScene->Render(*shaderShadowMapping);
	currentScene->RenderScene(*shaderShadowMapping);
	currentScene->DrawGizmo();
	currentScene->renderer.OpenGlRenderToImgui->UnBind();


	dockingSystem.UpdateDockSpace(*this, inputsEvents);


}



Project::Project() 
{




	resourcesManager.LoadAllAssets("ProjectFolder/Project1");
	currentScene = new Scene("Scene 0");
	currentScene->currentProject = this;
	mainCamera = Camera::cam;

	
	ContentBrowser::BasePath = "ProjectFolder/Project1";
	ContentBrowser::CurrentPath = ContentBrowser::BasePath;
	Gizmo::InitGizmo(*this);
	InitScene();
	Renderer::OpenGlRenderToImgui->InitResources();


}

Project::~Project()
{

	delete currentScene;
}











void Project::InitScene()
{
	
	//PyRun_SimpleString("sys.path.append(\".\")");
	//PyRun_SimpleString("sys.path.append(\"C:/Projet/ModernOpenglGB/source/include/Core/Python\")");


	// UPDATE PHYSICS FIRST
	currentScene->AddSystem(new PhysicsSystem());
	// Check Collsiion for nextframe
	currentScene->AddSystem(new ColliderSystem());
	// UPDATE MATRIX 
	currentScene->AddSystem(new GraphScene());



	currentScene->AddSystem(new RendererShadowSystem());
	currentScene->AddSystem(new RendererLightSystem());
	currentScene->AddSystem(new SystemRendererSkyMap());

	
	

	
	Entity* Directionnale = currentScene->CreateEntity();
	currentScene->GetComponent<Transform>(Directionnale)->pos = Vector3(-2.0f, 7, -1.0f);
	currentScene->AddComponent<DirectionalLight>(Directionnale);
	Directionnale->entityName = "Directional";

	Entity* ground = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(ground);
	currentScene->GetComponent<Transform>(ground)->scaling = Vector3(10, 1, 10);
	ground->entityName = "Ground";
	MeshRenderer* meshRenderer = currentScene->GetComponent<MeshRenderer>(ground);
	meshRenderer->mesh = *resourcesManager.GetElement<Mesh>("cube.obj");
	meshRenderer->material.diffuse = *resourcesManager.GetElement<Texture>("woodenGround.jpg");
	meshRenderer->material.specular = *resourcesManager.GetElement<Texture>("woodenGround.jpg");
	meshRenderer->material.ka = 0.4;
	meshRenderer->material.kd = 0.3;
	meshRenderer->material.ks = 0.2;
	meshRenderer->material.shininess = 10;


	// Cue

	Entity* Cube = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(Cube);
	currentScene->GetComponent<Transform>(Cube)->pos = Vector3(0, 2.5, 0);

	MeshRenderer* meshRendererCube = currentScene->GetComponent<MeshRenderer>(Cube);
	meshRendererCube->mesh = *resourcesManager.GetElement<Mesh>("cube.obj");
	meshRendererCube->material.diffuse = *resourcesManager.GetElement<Texture>("EmerauldBlock.png");
	meshRendererCube->material.specular = *resourcesManager.GetElement<Texture>("EmerauldBlock.png");
	meshRendererCube->material.ka = 0.5;
	meshRendererCube->material.kd = 0.7;
	meshRendererCube->material.ks = 0.75;
	meshRendererCube->material.shininess = 80;

	currentScene->Init();

}
