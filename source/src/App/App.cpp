#include "App/App.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include <Ressources/Model/Model.h>
#include <Ressources/Shader/Shader.h>
#include <Ressources/Texture/Texture.hpp>
#include <LowRenderer/Cam/Camera.h>   
#include "LowRenderer/FrameBuffer/ShadowMap/ShadowMaps.h"
#include "LowRenderer/FrameBuffer/MultiSamples/MultiSamples.h"
#include "Ressources/Scene/Scene.h"
#include <Ressources/RessourcesManager/RessourcesManager.h>

#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"
#include "External/yaml-cpp/yaml.h"
#include "LowRenderer/RendererSystem/RendererSystem.hpp"
#include "LowRenderer/MeshRenderer/MeshRenderer.h"

#include "Physics/Transform/Transform.hpp"
#include "LowRenderer/RendererLightSystem/RendererLightSystem.hpp"
#include "LowRenderer/Light/DirectionalLight/DirectionalLight.hpp"
#include "LowRenderer/Light/SpothLight/SpothLight.hpp"
#include "LowRenderer/Light/PointLight/PointLight.hpp"

Scene* App::currentScene = nullptr;
bool App::GammaCorrection = false;

void App::DrawSkyBox()
{
	Shader* SkyBoxShader = m_Ressources->GetElement<Shader>("SkyBoxShader");
	SkyBoxShader->Use();
	m_CurrentSkybox->Draw();

}


void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	currentScene->OpenGlRenderToImgui->ResizeFrammeBuffer(width, height);
}

void App::AppUpdate()
{
	currentScene->io = m_io;




	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	

	currentScene->OpenGlRenderToImgui->Bind();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	currentScene->cam->SetCameraInfoForShaders(*m_Ressources);
	DrawSkyBox();

	currentScene->cam->CameraUpdate();

	currentScene->FixedUpdate();
	currentScene->Update();
	currentScene->Render();
;



	currentScene->OpenGlRenderToImgui->UnBind();



	DockSpace();
	ImguiAppInfo();

	
}






void App::InitRessources()
{
	Depthmap* depthMap = new Depthmap();
	m_Ressources->PushBackElement("depthMap", depthMap);
	
	ShadowMaps* shadowMaps = new ShadowMaps(1024, 1024);
	m_Ressources->PushBackElement("shadowMaps", shadowMaps);

	
	std::vector<std::string> cubemapsSpaceString =
	{
		"assets/cube_maps/skybox/SpaceSkyBox/bkg1_right.png",
		"assets/cube_maps/skybox/SpaceSkyBox/bkg1_left.png",
		"assets/cube_maps/skybox/SpaceSkyBox/bkg1_top.png",
		"assets/cube_maps/skybox/SpaceSkyBox/bkg1_bottom.png",
		"assets/cube_maps/skybox/SpaceSkyBox/bkg1_front.png",
		"assets/cube_maps/skybox/SpaceSkyBox/bkg1_back.png",

	};
	CubeMaps cubemaps(cubemapsSpaceString);
	SkyBox* spaceSkybox = new SkyBox(cubemaps);
	m_Ressources->PushBackElement<SkyBox>("SpaceSkyBox", spaceSkybox);

	std::vector<std::string> cubemapsSkyString =
	{
		"assets/cube_maps/skybox/SkySkybox/right.jpg",
		"assets/cube_maps/skybox/SkySkybox/left.jpg",
		"assets/cube_maps/skybox/SkySkybox/top.jpg",
		"assets/cube_maps/skybox/SkySkybox/bottom.jpg",
		"assets/cube_maps/skybox/SkySkybox/front.jpg",
		"assets/cube_maps/skybox/SkySkybox/back.jpg",

	};
	CubeMaps cubemaps2(cubemapsSkyString);
	SkyBox* SkySkybox = new SkyBox(cubemaps2);
	m_Ressources->PushBackElement<SkyBox>("SkySkybox", SkySkybox);
	m_CurrentSkybox = m_Ressources->GetElement<SkyBox>("SpaceSkyBox");
	
	GizmoShader = m_Ressources->GetElement<Shader>("GizmoShader");


}

void App::InitScene()
{
	Scene::ressourcesManagers = m_Ressources;




	
	Scene* Level1 = new Scene("Scene1");
	m_Ressources->PushBackElement<Scene>("Scene1", Level1);
	App::currentScene = Level1;

	RendererSystem* rendererSystem = new RendererSystem();
	rendererSystem->shaderName = "NormalShader";
	Level1->m_register.Systems.push_back(rendererSystem);

	RendererLightSystem* lightRenderer = new RendererLightSystem();
	lightRenderer->shaderName = "NormalShader";
	Level1->m_register.Systems.push_back(lightRenderer);



	Entity* entity =  Level1->m_register.CreateEntity();
	Level1->m_register.AddComponent<MeshRenderer>(entity);

	MeshRenderer* meshRenderer = Level1->m_register.GetComponent<MeshRenderer>(entity);
	meshRenderer->model = m_Ressources->GetElement<Model>("viking_room.obj");
	meshRenderer->diffuse = m_Ressources->GetElement<Texture>("EmerauldBlock.png");
	meshRenderer->specular = m_Ressources->GetElement<Texture>("EmerauldBlock.png");
	


	Entity* entity2 = Level1->m_register.CreateEntity();
	Level1->m_register.GetComponent<Transform>(entity2)->pos = Vector3(2, 2, 2);
	Level1->m_register.AddComponent<DirectionalLight>(entity2);

	Level1->Init();

	

}




App::App(int _WindowX, int _WindowY, ImGuiIO& _io) : windowX(_WindowX), windowY(_WindowY) , m_io(_io)
{
	
	m_Ressources = new RessourcesManager();
	m_Ressources->LoadAllAssets();
	m_ContentBrowser = new ContentBrowser();
	m_io = ImGui::GetIO();

	InitRessources();
	InitScene();
	InitImguiTheme();
	
	Shader* skyboxShader = m_Ressources->GetElement<Shader>("SkyBoxShader");
	skyboxShader->Use();
	skyboxShader->SetInt("skybox", 30);
	
	// We Init The FrameBuffer here because we need To wait To Glad and opengl to be init
	Scene::OpenGlRenderToImgui->Init();



}


App::~App()
{
	delete m_Ressources;
}



#pragma region ImguiWindow

void App::ImguiInspector()  
{
	static bool open = true;
	if (ImGui::Begin("Inpsector"))
	{
		

		ImGui::PushID("");

		if (InspectorCurrentindow)
			InspectorCurrentindow->OnSelected();
		

		ImGui::PopID();

			
		
		ImGui::End();
	}

}





void App::ImguiGraphScene() 
{
	static bool open = true;

	if (!currentScene)
		return;

	
	if (ImGui::Begin("GraphScene",&open))
	{
		
		for (Entity* entity : currentScene->m_register.entities)
		{
			Transform* transfrom = currentScene->m_register.GetComponent<Transform>(entity);
			if (!transfrom->Parent)
			{
				ImguiDrawChildren(entity);

			}
		}

		
		ImGui::End();
	}

}

void App::ImguiDrawChildren(Entity* entity)
{
	
	Transform* transform = currentScene->m_register.GetComponent<Transform>(entity);
	bool hasChildren = !transform->childs.empty();
	static bool open = true;


	ImGuiTreeNodeFlags_ flags ;
	if (hasChildren)
	{
		flags = ImGuiTreeNodeFlags_None;
	}
	else
	{
		flags = ImGuiTreeNodeFlags_Leaf;
	}

	ImGui::PushID("");

	if (ImGui::TreeNodeEx(entity->Entityname.c_str(), flags))
	{
		/*
		if (ImGui::IsItemClicked())
			InspectorCurrentindow = entity;
		*/


		if (hasChildren)
		{
			for (size_t i = 0; i < transform->childs.size(); i++)
			{
				ImguiDrawChildren(transform->childs[i]->entity);
			}
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
	
}






void App::ImguiAppInfo() 
{



	if (ImGui::Begin("App Info"))
	{
		ImGui::Text("%f", m_io.Framerate);
		ImGui::Checkbox("PostProcess", &m_PostProcess);
		ImGui::Button("SaveCurrentScene");

		ImGui::Text("Type of CubeMap");
		if(ImGui::Button("Skybox Space"))
		{
			m_CurrentSkybox = m_Ressources->GetElement<SkyBox>("SpaceSkyBox");
		}
		if (ImGui::Button("Skybox Sky"))
		{
			m_CurrentSkybox = m_Ressources->GetElement<SkyBox>("SkySkybox");
		}

		ImGui::End();
	}

}

void App::DockSpace() 
{

	// Create docking layout
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
	if (opt_fullscreen)
		dockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus  | ImGuiWindowFlags_NoBackground;
	}

	// Begin docking layout
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);
	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	ImGuiID dockspaceID = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

	// Create windows
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open")) {}
			if (ImGui::MenuItem("Save")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}


	

	currentScene->cam->ImguiCameraWindow();
	ImguiGraphScene();
	m_ContentBrowser->Update(*this);
	ImguiInspector();

	ImGui::End();


}

#pragma endregion
#pragma region Imgui Theme
void App::InitImguiTheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameBorderSize = 0.0f;
}
#pragma endregion