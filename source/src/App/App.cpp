#include "App/App.h"
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
#include "Core/Input/PlayerMovement.h"	
#include "Collider/BoxCollider/BoxCollider.h"
#include "Scripts/KillZone.h"
#include "LowRenderer/Ui/UIRenderer.h"
#include "Physics/CollisionType/BoxCollisionType.h"


bool App::GammaCorrection = false;

void App::DrawSkyBox()
{
	Shader* SkyBoxShader = m_Ressources->GetElement<Shader>("SkyBoxShader");
	SkyBoxShader->Use();
	m_CurrentSkybox->Draw();
}

void App::GetInputOutPout(const ImGuiIO& io)
{
	m_io = io;
}


void App::AppUpdate()
{
	
	MultiSamples* sample = m_Ressources->GetElement<MultiSamples>("Msaa");
	FrameBuffer* postprocess = m_Ressources->GetElement<FrameBuffer>("PostProcess");
	Shader* GizmoShader = m_Ressources->GetElement<Shader>("GizmoShader");
	Shader* baseShader = m_Ressources->GetElement<Shader>("NormalShader");
	Shader* Stencil = m_Ressources->GetElement<Shader>("StencilTest");
	Shader* UiRender = m_Ressources->GetElement<Shader>("UiShader");



	sample->Bind();	
	currentScene->cam->SetCameraInfoForShaders(*m_Ressources);
	DrawSkyBox();

	Inputs.UpdatePlayerInput(this, *m_Ressources);
	currentScene->PhyscisUpdate();
	currentScene->SceneUpdate(m_io);
	currentScene->RenderScene(baseShader,Stencil);
	currentScene->RenderGizmo(GizmoShader);
	currentScene->RenderUi(UiRender);

	if (m_PostProcess)
	{
		sample->BlitBuffers(postprocess->FBO);
	}
	else
	{
		sample->BlitBuffers(0);
	}
	if (m_PostProcess)
	{
		postprocess->DrawBuffer(*m_CurrentPostProcess);
	}

	currentScene->LateUpdate();
	if(Inputs.CurrentPlayerScene != MENUE)
	{
		ImguiInspector();
		currentScene->cam->ImguiCameraWindow();
		ImguiGraphScene();
		ImguiAppInfo();	
	}
	
}




void App::InitRessources()
{
	FrameBuffer* postProcess = new FrameBuffer(windowWidth, windowHeight);
	m_Ressources->PushBackElement("PostProcess", postProcess);

	ShadowMaps* shadowMaps = new ShadowMaps(2048, 2048);
	m_Ressources->PushBackElement("shadowMaps", shadowMaps);

	MultiSamples* msaa = new MultiSamples(MSAA);
	m_Ressources->PushBackElement("Msaa", msaa);

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
	Scene* Menue = new Scene("Menue");
	Scene* Level1 = new Scene("Level1");
	m_Ressources->PushBackElement<Scene>("Menue", Menue);
	Menue->ressourcesManagers = m_Ressources;
	m_Ressources->PushBackElement<Scene>("Level1", Level1);
	Level1->ressourcesManagers = m_Ressources;

	currentScene = Level1;
	////// Menue ///////



	/////////////////////////////// Game /////////////////////////

	Model* nethriPlateform = m_Ressources->GetElement<Model>("cube.obj");
	Texture* Diamond = m_Ressources->GetElement<Texture>("DiamondBlock.jpg");

	Entity* DirectionnalLight = new Entity("Directionnal Light", Level1);
	DirectionnalLight->transform.pos += Vector3(-2.0f, 4.0f, -1.0f);
	Vector4 ambiantColor = Vector4(0.1f, 0.2f, 0.5f, 1);
	Vector4 diffuseColor = Vector4(0.1f, 0.1f, 0.1f, 0.1f);
	Vector4 specular = Vector4(0.2f, 0.2f, 0.2f, 0.2f);
	DirectionalLight* directionalight = new DirectionalLight(*DirectionnalLight);




	directionalight->ambiant = ambiantColor;
	directionalight->diffuse = diffuseColor;

	directionalight->specular = specular;
	DirectionnalLight->AddComponent(directionalight);

	Level1->entities.push_back(DirectionnalLight);





	
	Entity* TestCollider1 = new Entity("Test Sphere Collider", Level1);
	TestCollider1->transform.pos = Vector3(-4, 5, 0);
	TestCollider1->AddComponent(new SphereCollider(*TestCollider1, 1.f));
	Level1->m_PhysicsEngine.allCollider.push_back(TestCollider1->GetComponent<SphereCollider>());
	Level1->entities.push_back(TestCollider1);
	




	
	Entity* Ground = new Entity("Ground", Level1);
	Ground->Tag = "Ground";
	Ground->transform.pos = Vector3(0, -15, 0);




	Ground->AddComponent(new PlaneCollider(*Ground));
	Ground->GetComponent<PlaneCollider>()->CollisionShape[0] = new PlaneCollision(*Ground, Vector3(5, 0, 0), Vector3(0, 0, 5), true);
	Level1->entities.push_back(Ground);
	Level1->m_PhysicsEngine.allCollider.push_back(Ground->GetComponent<PlaneCollider>());
	Ground->AddComponent(new KillZone(*Ground));
	/*
	Entity* Box = new Entity("Box", Level1);
	Box->Tag = "Ground";
	Box->transform.pos = Vector3(2, -2, 0);
	Box->AddComponent(new BoxCollider(*Box, Vector3(10,10,10)));
	entities.push_back(Box);
	m_PhysicsEngine.allCollider.push_back(Box->GetComponent<BoxCollider>());
	*/

	
	Entity* Box2 = new Entity("Box2", Level1);
	Box2->transform.pos = Vector3(0, -2, 0);
	Box2->transform.scale = Vector3(5, 1, 5);
	Box2->Tag = "Ground";
	Texture* nethrite = m_Ressources->GetElement<Texture>("NethriteBlock.jpg");
	Box2->AddComponent(new MeshRenderer(*nethriPlateform, *nethrite, *Box2));
	Box2->AddComponent(new BoxCollider(*Box2, Box2->transform.scale));
	Level1->entities.push_back(Box2);
	Level1->m_PhysicsEngine.allCollider.push_back(Box2->GetComponent<BoxCollider>());




	Entity* Box3 = new Entity("Box3", Level1);
	Box3->transform.pos = Vector3(20, -2, 0);
	Box3->transform.scale = Vector3(5, 1, 9);
	Box3->Tag = "Ground";
	Box3->AddComponent(new MeshRenderer(*nethriPlateform, *nethrite, *Box3));
	Box3->AddComponent(new BoxCollider(*Box3, Box3->transform.scale));
	Level1->entities.push_back(Box3);
	Level1->m_PhysicsEngine.allCollider.push_back(Box3->GetComponent<BoxCollider>());

	

	Entity* Box4 = new Entity("Box4", Level1);
	Box4->transform.pos = Vector3(40, 2, 13);
	Box4->transform.scale = Vector3(5, 1.3, 10);
	Box4->Tag = "Ground";
	Box4->AddComponent(new MeshRenderer(*nethriPlateform, *nethrite, *Box4));
	Box4->AddComponent(new BoxCollider(*Box4, Box4->transform.scale));
	Level1->entities.push_back(Box4);
	Level1->m_PhysicsEngine.allCollider.push_back(Box4->GetComponent<BoxCollider>());



	Entity* Box5 = new Entity("Box5", Level1);
	Box5->transform.pos = Vector3(40, 2, 40);
	Box5->transform.scale = Vector3(10, 1.2 , 6);
	Box5->Tag = "Ground";
	Box5->AddComponent(new MeshRenderer(*nethriPlateform, *Diamond, *Box5));
	Box5->AddComponent(new BoxCollider(*Box5, Box5->transform.scale));
	Level1->entities.push_back(Box5);
	Level1->m_PhysicsEngine.allCollider.push_back(Box5->GetComponent<BoxCollider>());


	Entity* Box6 = new Entity("Box6", Level1);
	Box6->transform.pos = Vector3(65,0.60, 38.40);
	Box6->transform.scale = Vector3(10, 1.4, 6);
	Box6->Tag = "Ground";
	Box6->AddComponent(new MeshRenderer(*nethriPlateform, *Diamond, *Box6));
	Box6->AddComponent(new BoxCollider(*Box6, Box6->transform.scale));
	Level1->entities.push_back(Box6);
	Level1->m_PhysicsEngine.allCollider.push_back(Box6->GetComponent<BoxCollider>());



	Entity* Box7 = new Entity("Box7", Level1);
	Box7->transform.pos = Vector3(10, 2, 50);
	Box7->transform.scale = Vector3(10, 1, 6);
	Box7->Tag = "Ground";
	Box7->AddComponent(new MeshRenderer(*nethriPlateform, *Diamond, *Box7));
	Box7->AddComponent(new BoxCollider(*Box7, Box7->transform.scale));
	Level1->entities.push_back(Box7);
	Level1->m_PhysicsEngine.allCollider.push_back(Box7->GetComponent<BoxCollider>());


	Entity* Box8 = new Entity("Box8", Level1);
	Box8->transform.pos = Vector3(10, 2, 100);
	Box8->transform.scale = Vector3(30, 1, 30);
	Box8->Tag = "Ground";
	Box8->AddComponent(new MeshRenderer(*nethriPlateform, *Diamond, *Box8));
	Box8->AddComponent(new BoxCollider(*Box8, Box8->transform.scale));
	Level1->entities.push_back(Box8);
	Level1->m_PhysicsEngine.allCollider.push_back(Box8->GetComponent<BoxCollider>());


	Texture* RedWoo = m_Ressources->GetElement<Texture>("Red_Wool.png");

	Entity* Box9 = new Entity("Box9", Level1);
	Box9->transform.pos = Vector3(60, 2, 100);
	Box9->transform.scale = Vector3(10, 1, 10);
	Box9->Tag = "Ground";
	Box9->AddComponent(new MeshRenderer(*nethriPlateform, *RedWoo, *Box9));
	Box9->AddComponent(new BoxCollider(*Box9, Box9->transform.scale));
	Level1->entities.push_back(Box9);
	Level1->m_PhysicsEngine.allCollider.push_back(Box9->GetComponent<BoxCollider>());



	Entity* Box10 = new Entity("Box10", Level1);
	Box10->transform.pos = Vector3(-45, -4.6, 30);
	Box10->transform.scale = Vector3(30, 1, 30);
	Box10->Tag = "Ground";
	Box10->AddComponent(new MeshRenderer(*nethriPlateform, *RedWoo, *Box10));
	Box10->AddComponent(new BoxCollider(*Box10, Box10->transform.scale));
	Level1->entities.push_back(Box10);
	Level1->m_PhysicsEngine.allCollider.push_back(Box10->GetComponent<BoxCollider>());



	Entity* Box11 = new Entity("Box11", Level1);
	Box11->transform.pos = Vector3(13.6, -1.2, 18.4);
	Box11->transform.scale = Vector3(10, 1, 10);
	Box11->Tag = "Ground";
	Box11->AddComponent(new MeshRenderer(*nethriPlateform, *RedWoo, *Box11));
	Box11->AddComponent(new BoxCollider(*Box11, Box11->transform.scale));
	Level1->entities.push_back(Box11);
	Level1->m_PhysicsEngine.allCollider.push_back(Box11->GetComponent<BoxCollider>());





	Entity* Box12 = new Entity("Box12", Level1);
	Box12->transform.pos = Vector3(-61, -1.40, 95);
	Box12->transform.scale = Vector3(30, 1, 30);
	Box12->Tag = "Ground";
	Box12->AddComponent(new MeshRenderer(*nethriPlateform, *RedWoo, *Box12));
	Box12->AddComponent(new BoxCollider(*Box12, Box12->transform.scale));
	Level1->entities.push_back(Box12);
	Level1->m_PhysicsEngine.allCollider.push_back(Box12->GetComponent<BoxCollider>());

	

	Entity* Player = new Entity("Player", Level1);
	Player->transform.scale = Vector3(0.01, 0.01, 0.01);
	Player->Tag = "Player";
	Model* dode = m_Ressources->GetElement<Model>("dodecahedron.obj");
	Texture* Emerauld = m_Ressources->GetElement<Texture>("EmerauldBlock.png");
	Player->transform.pos = Vector3(0, 0, 0);
	Player->AddComponent(new MeshRenderer(*dode,*Emerauld,*Player));
	Player->AddComponent(new SphereCollider(*Player, 1.f));
	Player->GetComponent<SphereCollider>()->Gizmorenderer->IsDrawing = false;

	Level1->m_PhysicsEngine.allCollider.push_back(Player->GetComponent<SphereCollider>());
	Player->AddComponent(new Rigidbody(*Player, *Player->GetComponent<Collider>()));
	Player->GetComponent<Rigidbody>()->mass = 0.5f;
	Level1->entities.push_back(Player);
	Player->AddComponent(new  PlayerMovement(*Player));


	Level1->cam->playerMovment = Player->GetComponent<PlayerMovement>();
	Level1->cam->viewTarget = &Player->transform;


	Entity* Uitest = new Entity("UI Test",Level1);
	Uitest->AddComponent(new UIRenderer(*Uitest));
	Level1->entities.push_back(Uitest);

	/// <summary>
	/// Test Box Collider 6 PLans ended
	/// </summary>
	/*
	Entity* TestBoxCollision = new Entity("BoxColliderTest", Level1);
	TestBoxCollision->transform.rotate += Vector3(0, 0, 0);
	TestBoxCollision->transform.pos = Vector3(0, 0, 0);
	BoxCollider* boxCollider = new BoxCollider(*TestBoxCollision);
	delete boxCollider->CollisionShape[0];
	boxCollider->CollisionShape.clear();
	BoxCollisionType* boxcoll = new BoxCollisionType(*TestBoxCollision);
	boxCollider->CollisionShape.push_back(boxcoll);
	TestBoxCollision->AddComponent(boxCollider);
	Level1->entities.push_back(TestBoxCollision);
	Level1->m_PhysicsEngine.allCollider.push_back(TestBoxCollision->GetComponent<BoxCollider>());
	*/
	
}



App::App(int _WindowX, int _WindowY, ImGuiIO& _io) : windowX(_WindowX), windowY(_WindowY) , m_io(_io)
{
	
	m_Ressources = new RessourcesManager();
	m_Ressources->LoadAllAssets();
	InitRessources();

	InitScene();


	InitImguiTheme();
	Shader* skyboxShader = m_Ressources->GetElement<Shader>("SkyBoxShader");
	skyboxShader->Use();
	skyboxShader->SetInt("skybox", m_CurrentSkybox->m_Cubemaps.cubeMapIndex);
	StaticRessourcesManger = m_Ressources;
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
				ImguiDrawChildren(&entity->transform.Childrens[i]->EntityAttachTo);
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
	
		ImGui::Text("Gamma Correction change on runtime not working");
		/*
		if(ImGui::Checkbox("Applied GammaCorrection",&App::GammaCorrection))
		{
			m_Ressources->RealoadAllTexture();
		}
		*/

		ImGui::Text("Type of CubeMap");
		if(ImGui::Button("Skybox Space"))
		{
			m_CurrentSkybox = m_Ressources->GetElement<SkyBox>("SpaceSkyBox");
		}
		if (ImGui::Button("Skybox Sky"))
		{
			m_CurrentSkybox = m_Ressources->GetElement<SkyBox>("SkySkybox");
		}
		ImGui::Text("Type of postprocess");
		if (ImGui::Button("KernelEffect"))
		{
			m_CurrentPostProcess = m_Ressources->GetElement<Shader>("KernelEffectShader");
		}
		if (ImGui::Button("Invert color"))
		{
			m_CurrentPostProcess = m_Ressources->GetElement<Shader>("InvertShader");
		}


		ImGui::End();
	}

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