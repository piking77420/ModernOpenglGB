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
#include "Core/ECS/PythonScript.h"

#include"App/App.h"

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
	Cube1rdr->mesh = *resourcesManager.GetElement<Mesh>("viking_room.obj");
	Cube1rdr->material.diffuse = *resourcesManager.GetElement<Texture>("Viking_room.png");
	Cube1rdr->material.specular = *resourcesManager.GetElement<Texture>("Viking_room.png");

	Entity* Cube2 = currentScene->CreateEntity();
	currentScene->AddComponent<MeshRenderer>(Cube2);
	currentScene->AddComponent<BoxCollider>(Cube2);
	currentScene->GetComponent<Transform>(Cube2)->pos = Vector3(-4.0f, 5.0f, -3.0f);

	currentScene->GetComponent<Transform>(Cube2)->pos = Vector3(-2.0f, 4.0f, -1.0f);
	MeshRenderer* Cube2rdr = currentScene->GetComponent<MeshRenderer>(Cube2);
	Cube2rdr->mesh = *resourcesManager.GetElement<Mesh>("viking_room.obj");
	Cube2rdr->material.diffuse = *resourcesManager.GetElement<Texture>("Viking_room.png");
	Cube2rdr->material.specular = *resourcesManager.GetElement<Texture>("Viking_room.png");

	PythonScript* pt = resourcesManager.GetElement<PythonScript>("CorePython.py");
	currentScene->AddSystem(pt);

	currentScene->Init();

}
