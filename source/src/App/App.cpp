#include "App/App.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include "LowRenderer/RendererComponent/MeshRenderer/MeshRenderer.h"
#include <LowRenderer/Light/Light.h>
#include <Ressources/Model/Model.h>
#include <Ressources/Shader/Shader.h>
#include <Ressources/Texture/Texture.hpp>
#include <LowRenderer/Cam/Camera.h>   
#include "LowRenderer/FrameBuffer/ShadowMap/ShadowMaps.h"
#include "LowRenderer/FrameBuffer/MultiSamples/MultiSamples.h"
#include "Ressources/Scene/Scene.h"
#include <Ressources/RessourcesManager/RessourcesManager.h>
#include "Core/DataStructure/Component/Collider/SphereCollider/SphereCollider.h"
#include "Core/DataStructure/Component/Collider/PlaneCollider.h"
#include "Core/DataStructure/Entity/Entity.h"
#include "Collider/BoxCollider/BoxCollider.h"
#include "LowRenderer/Ui/UIRenderer.h"
#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"
#include "External/yaml-cpp/yaml.h"
#include "Collider/SphereCollider/SphereCollider.h"

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
	
	Shader* GizmoShader = m_Ressources->GetElement<Shader>("GizmoShader");
	Shader* baseShader = m_Ressources->GetElement<Shader>("NormalShader");
	Shader* Stencil = m_Ressources->GetElement<Shader>("StencilTest");


	currentScene->OpenGlRenderToImgui->Bind();
	glClearColor(0.4f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	currentScene->cam->SetCameraInfoForShaders(*m_Ressources);
	DrawSkyBox();

	currentScene->cam->CameraUpdate();
	currentScene->SceneUpdate(m_io);
	currentScene->RenderScene(baseShader, Stencil);
	currentScene->RenderGizmo(GizmoShader);

	
	
	

	currentScene->OpenGlRenderToImgui->UnBind();


	DockSpace();
	ImguiAppInfo();

	
	
}






void App::InitRessources()
{
	Depthmap* depthMap = new Depthmap();
	m_Ressources->PushBackElement("depthMap", depthMap);

	ShadowMaps* shadowMaps = new ShadowMaps(2048, 2048);
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
	m_CurrentPostProcess = m_Ressources->GetElement<Shader>("KernelEffectShader");


}

void App::InitScene()
{

	
	Scene* Level1 = new Scene("Scene1");
	m_Ressources->PushBackElement<Scene>("Scene1", Level1);
	Level1->ressourcesManagers = m_Ressources;	
	App::currentScene = Level1;




	Entity* DirectionnalLight = new Entity("Directionnal Light", Level1);
	DirectionnalLight->AddComponent<DirectionalLight>();



   Entity* vikingroom = new Entity("VikingRoom", Level1);
   vikingroom->AddComponent<MeshRenderer>();
   vikingroom->AddComponent<SphereCollider>();


   Entity* Sphre2 = new Entity("Sphre2", Level1);
   //Sphre2->AddComponent<MeshRenderer>();
   Sphre2->AddComponent<SphereCollider>();
   Sphre2->transform.SetPos() += Vector3(5, 5,0);
   

	Level1->entities.push_back(DirectionnalLight);
	Level1->entities.push_back(vikingroom);
	Level1->entities.push_back(Sphre2);


	// Set Currentscene
}




App::App(int _WindowX, int _WindowY, ImGuiIO& _io) : windowX(_WindowX), windowY(_WindowY) , m_io(_io)
{
	
	m_Ressources = new RessourcesManager();
	m_Ressources->LoadAllAssets();
	m_ContentBrowser = new ContentBrowser();
	Scene::ressourcesManagers = m_Ressources;
	m_io = ImGui::GetIO();

	InitRessources();
	InitScene();
	InitImguiTheme();
	Shader* skyboxShader = m_Ressources->GetElement<Shader>("SkyBoxShader");
	skyboxShader->Use();
	skyboxShader->SetInt("skybox", m_CurrentSkybox->m_Cubemaps.slot);

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
	if (ImGui::Begin("GraphScene",&open))
	{
		if (ImGui::Button("Add entites"))
			currentScene->AddEntity();

		for (size_t i = 0; i < currentScene->entities.size(); i++)
		{
			if (!currentScene->entities[i]->HasParent())
			{
				ImguiDrawChildren(currentScene->entities[i]);
			}
		}
		ImGui::End();
	}

}

void App::ImguiDrawChildren(Entity* entity) 
{
	bool hasChildren = !entity->transform.Childrens.empty();
	static bool open = true;


	ImGuiTreeNodeFlags_ flags;
	if (hasChildren)
	{
		flags = ImGuiTreeNodeFlags_None;
	}
	else
	{
		flags = ImGuiTreeNodeFlags_Leaf;
	}

	ImGui::PushID("");

	if (ImGui::TreeNodeEx(entity->name.c_str(), flags))
	{
	
		if (ImGui::IsItemClicked())
			InspectorCurrentindow = entity;

		if (hasChildren)
		{
			for (size_t i = 0; i < entity->transform.Childrens.size(); i++)
			{
				ImguiDrawChildren(entity->transform.Childrens[i]->EntityAttachTo);
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
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
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

	if (ImGui::Begin("Render "))
	{
		float width = ImGui::GetContentRegionAvail().x;
		float height = ImGui::GetContentRegionAvail().y;
	
		ImGui::Image((ImTextureID)currentScene->OpenGlRenderToImgui->framebufferTexture, ImGui::GetContentRegionAvail(),
			ImVec2(0, 1),
			ImVec2(1, 0));
		ImGui::End();
	}

	

	ImguiInspector();
	currentScene->cam->ImguiCameraWindow();
	ImguiGraphScene();
	m_ContentBrowser->Update(*this);

	ImGui::End();


}

#pragma endregion
#pragma region Imgui Theme
void App::InitImguiTheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameBorderSize = 0.5f;
}
#pragma endregion