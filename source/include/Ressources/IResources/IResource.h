#pragma once
#include<Core/CoreEngine.h>
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include "UI/InspectorSelectable.h"
namespace fs = std::filesystem;



class IResource 
{
public:
	virtual void InitResource() {  };
	virtual ~IResource() {};
	virtual void DeleteResource() { };
	virtual void Reload() { };
}; 



	