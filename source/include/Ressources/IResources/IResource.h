#pragma once
#include <iostream>
#include <string>
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include<filesystem>
#include "UI/InspectorSelectable.h"
namespace fs = std::filesystem;


class IResource : public InspectorSelectable
{
public:

	virtual void Init() {  };
	virtual ~IResource();
	virtual void OnWindowResize(){};

protected:
}; 