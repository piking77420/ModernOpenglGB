#pragma once
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<DataStructure/ComponentsBehaviours.h>
#include "Ressources/SkyBox/SkyBox.h"
#include "Ressources/CubeMaps/CubeMaps.h"
#include "UI/InspectorSelectable.h"

#include <Core/Debug/Debug.h>

#include "Mathf.h"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include "UI/ContentBrowser.h"


class RessourcesManager;
class Camera;
class Texture;
class Shader;
class Model;
class Light;

const int windowWidth = 1920;
const int windowHeight = 1080;
const int MSAA = 8;


class App
{
public:	

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void AppUpdate(); 
	bool HasPlayOnce;
	static bool GammaCorrection;	
	static Scene* currentScene;
	RessourcesManager* m_Ressources;	
	InspectorSelectable* InspectorCurrentindow;
	App(int _WindowX, int _WindowY, ImGuiIO& _io);
	~App();
private:
	ImGuiIO& m_io;
	bool m_PostProcess;
	const int windowX;
	const int windowY;
	void InitRessources();
	void InitScene();
	void DrawSkyBox();
	void InitImguiTheme();
	void ImguiInspector() ;
	void ImguiGraphScene() ;
	void ImguiAppInfo();
	void DockSpace() ;
	void ImguiDrawChildren(Entity* entity) ;
	SkyBox* m_CurrentSkybox;
	ContentBrowser* m_ContentBrowser;
	Shader* GizmoShader;
	Shader* BaseShader;
	Shader* Stencil;
};

