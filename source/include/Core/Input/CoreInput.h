#pragma once
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>

#include "InputEvent.h"
#include "Core/CoreEngine.h"





class CoreInput
{
public:


	// this function will send event on the vector to allow listing of the rest of listeners system 
	void LookForInput() ;

	void ClearInputs();

	static bool IsKeyPress(KeyCode keycode,bool consume = false);
	static bool IsKeyHold(KeyCode keycode,bool consume = false);
	static bool IsKeyRelease(KeyCode keycode,bool consume = false);

	static const Vector2& GetMousePos();


	static void InitCallBack(GLFWwindow* window);


	static inline GLFWwindow* windowPtr;

private:

	static inline bool FirstMouseMove = false;
	
	static inline std::vector<InputEvent> InputsEvents;
	static void ConsumeInput(std::uint32_t index);

	static void HandleKey(KeyCode key);
	static void HandleMouseButton();

	static KeyCode MouseKeyFromIndex(int index);

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	static inline Vector2 cameraPos;

};

