#pragma once
#include <iostream>
#include <string>
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include<filesystem>
namespace fs = std::filesystem;


class IResource
{
public:
	virtual IResource* Load(std::string path);
	virtual void Saving() {};
	virtual ~IResource();

protected:
	std::string pathLocation;
}; 