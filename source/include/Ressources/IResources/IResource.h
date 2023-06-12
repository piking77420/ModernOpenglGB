#pragma once
#include <iostream>
#include <string>
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>



class IResource
{
public:

	virtual ~IResource();
}; 