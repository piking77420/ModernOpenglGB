#include "App/App.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>
#include <Ressources/Model/Model.h>
#include <Ressources/Shader/Shader.h>
#include <Ressources/Texture/Texture.hpp>
#include <LowRenderer/Cam/Camera.h>   

#include "Ressources/Scene/Scene.h"
#include <Ressources/RessourcesManager/RessourcesManager.h>

#include "External/yaml-cpp/yaml.h"







void App::AppUpdate()
{

	CurrentProject.Update();
	
}


App::App(int _WindowX, int _WindowY, ImGuiIO& _io) : windowX(_WindowX), windowY(_WindowY) ,CurrentProject(Project("ProjectFolder/Project1"))
{
	
	

}


App::~App()
{
}








