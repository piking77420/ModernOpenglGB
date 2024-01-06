#include "Core/Input/CoreInput.h"
#include<GLFW/glfw3.h>




void CoreInput::LookForInput()
{

	for (size_t i = KEY_Tab; i < KEY_COUNT; i++)
	{
		HandleKey(static_cast<KeyCode>(i));
	}

	HandleMouseButton();
	/*
	for (size_t i = 0; i < InputsEvents.size(); i++)
	{
		std::cout << InputsEvents[i].ToString() << " " << EventTypeToString(InputsEvents[i].EventType) << std::endl;
	}
	*/
}

void CoreInput::ClearInputs()
{
	InputsEvents.clear();
}

bool CoreInput::IsKeyPress(KeyCode keycode, bool consume)
{

	for (size_t i = 0; i < InputsEvents.size(); i++)
	{

		if (InputsEvents[i].EventType != KEYPRESS)
			continue;

		if (InputsEvents[i].keycode == keycode)
		{
			if(consume)
			{
				ConsumeInput(i);
			}

			return true;
		}

	}

	return false;
}

bool CoreInput::IsKeyHold(KeyCode keycode, bool consume)
{
	for (size_t i = 0; i < InputsEvents.size(); i++)
	{
		if (InputsEvents[i].EventType != KEYHOLD)
			continue;

		if (InputsEvents[i].keycode == keycode)
		{
			if (consume)
			{
				ConsumeInput(i);
			}

			return true;
		}

	}

	return false;
}

bool CoreInput::IsKeyRelease(KeyCode keycode, bool consume)
{
	for (size_t i = 0; i < InputsEvents.size(); i++)
	{
		if (InputsEvents[i].EventType != KEYRELEASE)
			continue;

		if (InputsEvents[i].keycode == keycode)
		{
			if (consume)
			{
				ConsumeInput(i);
			}

			return true;
		}

	}

	return false;
}

const Vector2& CoreInput::GetMousePos()
{
	ImVec2&& vec = ImGui::GetMousePos();
	return *reinterpret_cast<Vector2*>(&vec);
}


void CoreInput::ConsumeInput(std::uint32_t index)
{
	InputsEvents.erase(std::vector<InputEvent>::iterator() + index);
}

void CoreInput::HandleKey(KeyCode key)
{
	InputEvent newkey;
	newkey.keycode = key;

	if (ImGui::IsKeyDown(static_cast<ImGuiKey>(key)))
	{
		newkey.EventType = KEYHOLD;

		InputsEvents.emplace_back(newkey);

	}

	if (ImGui::IsKeyPressed(static_cast<ImGuiKey>(key), true))
	{
		newkey.EventType = KEYPRESS;

		InputsEvents.emplace_back(newkey);
	}



	if (ImGui::IsKeyReleased(static_cast<ImGuiKey>(key)))
	{
		newkey.EventType = KEYRELEASE;

		InputsEvents.emplace_back(newkey);
	}
}

void CoreInput::HandleMouseButton()
{
	auto& io = ImGui::GetIO();

	for (size_t i = 0; i < 5; i++)
	{
		KeyCode keycode = MouseKeyFromIndex(i);

		if(io.MouseClicked[i])
		{
			InputsEvents.push_back({ keycode,KEYPRESS });
		}

		if (io.MouseDown[i])
		{
			InputsEvents.push_back({ keycode,KEYHOLD });
		}

		if (io.MouseReleased[i])
		{
			InputsEvents.push_back({ keycode,KEYRELEASE });
		}
	}



}

KeyCode CoreInput::MouseKeyFromIndex(int index)
{
	int value = (int)KeyCode::MOUSE_Left + index;
	return (KeyCode)(value);
}

void CoreInput::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	int value = (int)MOUSE_Left + button;

	InputsEvents.push_back({ (KeyCode)value ,KEYPRESS });
}

void CoreInput::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	cameraPos = { static_cast<float>(xpos) ,static_cast<float>(ypos) };
}



void CoreInput::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
}

void CoreInput::InitCallBack(GLFWwindow* window)
{
	return; 

	// Set GLFW mouse button callback
	glfwSetMouseButtonCallback(window, CoreInput::MouseButtonCallback);


	// Set GLFW scroll callback
	glfwSetScrollCallback(window, CoreInput::ScrollCallback);

	glfwSetCursorPosCallback(window, CursorPositionCallback);

}
