#pragma once

#include<string>
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>


class Entity;
class AppData;
class Scene;

class Component
{
protected:
	bool IsEnabled = true;
	std::string m_ComponentName = "Base One";
public:

	Entity& EntityAttachTo;

	virtual void ImguiWindowComponents();	
	void ImguiWindow();
	virtual void PreUpdate(Scene* scene);
	virtual void Update(Scene* scene);
	virtual void LateUpdate(Scene* scene);


	Component(Entity& entity);	
};

