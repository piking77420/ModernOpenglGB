#pragma once
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<DataStructure/ComponentsBehaviours.h>
#include "Ressources/SkyBox/SkyBox.h"
#include "Ressources/CubeMaps/CubeMaps.h"

#include <Core/Debug/Debug.h>
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include "Mathf.h"



class RessourcesManager;
class Camera;
class Texture;
class Shader;
class Model;
class AppData;
class Light;

const int windowWidth = 1920;
const int windowHeight = 1080;
const int MSAA = 8;


class App
{
public:	


	void AppUpdate(); 

	static bool GammaCorrection;	
	static Scene* currentScene;
	RessourcesManager* m_Ressources;

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
	void ImguiInspector() const;
	void ImguiGraphScene() const;
	void ImguiAppInfo();
	void ImguiDrawChildren(Entity* entity) const;
	SkyBox* m_CurrentSkybox;
	Shader* m_CurrentPostProcess;
	

};

