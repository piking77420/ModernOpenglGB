#pragma once
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>

#include "InputEvent.h"






class InputEvent;

class CoreInput
{
public:


	// this function will send event on the vector to allow listing of the rest of listeners system 
	void LookForInput(std::vector<InputEvent*>& inputEvent) ;


private:
	void LookForKey(std::vector<InputEvent*>& inputEvent);
	void LookForMouse(std::vector<InputEvent*>& inputEvent);

};

