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
#include "Physics/CollisionType/BoxCollisionType.h"
#include "LowRenderer/FrameBuffer/DepthMap/Depthmap.h"

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

	currentScene->PhyscisUpdate();
	currentScene->cam->CameraUpdate();
	currentScene->SceneUpdate(m_io);
	currentScene->RenderScene(baseShader, Stencil);
	currentScene->RenderGizmo(GizmoShader);

	
	
	

	currentScene->LateUpdate();
	currentScene->OpenGlRenderToImgui->UnBind();


	DockSpace();
	ImguiAppInfo();

	ContentBrowser();
	
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



	Level1->entities.push_back(DirectionnalLight);
	Level1->entities.push_back(vikingroom);

	// Set Currentscene
}



App::App(int _WindowX, int _WindowY, ImGuiIO& _io) : windowX(_WindowX), windowY(_WindowY) , m_io(_io)
{
	
	m_Ressources = new RessourcesManager();
	RendererComponent::ressourcesManager = m_Ressources;
	m_Ressources->LoadAllAssets();

	m_io = ImGui::GetIO();

	InitRessources();
	InitScene();
	//InitImguiTheme();
	Shader* skyboxShader = m_Ressources->GetElement<Shader>("SkyBoxShader");
	skyboxShader->Use();
	skyboxShader->SetInt("skybox", m_CurrentSkybox->m_Cubemaps.slot);
	StaticRessourcesManger = m_Ressources;

	// We Init The FrameBuffer here because we need To wait To Glad and opengl to be init
	Scene::OpenGlRenderToImgui->Init();
}


App::~App()
{
	delete m_Ressources;
}



#pragma region ImguiWindow

void App::ImguiInspector() const 
{

	if (ImGui::Begin("Inpsector"))
	{
		if (ImGui::Button("Add entites"))
			currentScene->AddEntity();

		if (ImGui::CollapsingHeader("Entities"))
		{
			ImGui::PushID("");

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;


			for (size_t i = 0; i < currentScene->entities.size(); i++)
			{
				currentScene->entities[i]->ImguiEntityWindow();
			}

			ImGui::PopID();

			
		}
		ImGui::End();
	}

}





void App::ImguiGraphScene() const
{
	if (ImGui::Begin("GraphScene"))
	{
		

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

void App::ContentBrowser() const
{
	if(ImGui::Begin("Content browser"))
	{
		ImGui::End();
	}
}

void App::ImguiDrawChildren(Entity* entity) const
{
	bool hasChildren = !entity->transform.Childrens.empty();


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

void App::DockSpace() const
{
	//ImGui::ShowDemoWindow();

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
	ContentBrowser();

	ImGui::End();


}

#pragma endregion
#pragma region Imgui Theme
void App::InitImguiTheme()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(8.00f, 8.00f);
	style.FramePadding = ImVec2(5.00f, 2.00f);
	style.CellPadding = ImVec2(6.00f, 6.00f);
	style.ItemSpacing = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = 1;
	style.TabBorderSize = 1;
	style.WindowRounding = 7;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.LogSliderDeadzone = 4;
	style.TabRounding = 4;
}
#pragma endregion