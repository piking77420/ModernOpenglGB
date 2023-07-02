#pragma once

#include<string>
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>


class Entity;
class AppData;
class Scene;

class Component
{
protected:
	bool IsEnabled = true;
	std::string m_ComponentName = "Base One";
public:
	uint32_t m_ID;
	Entity* EntityAttachTo;
	virtual void ImguiWindowComponents();	
	void ImguiWindow();


	// Update Function // 
	virtual void PreUpdate(Scene* scene);
	virtual void Update(Scene* scene);
	virtual void LateUpdate(Scene* scene);
	virtual void FixedUpdate(Scene* scene);
	virtual void Renderer(Scene* scene);



	static uint32_t GlobalComponentID;

	Component();	

};

