#include "Core/Input/CoreInput.h"



#define HANDLEINPUT(key)\
if (ImGui::IsKeyPressed(key))\
{\
	inputEvent.push_back(new IsKeyPress(key));\
}\


void CoreInput::LookForInput(std::vector<InputEvent*>& inputEvent)
{
	LookForMouse(inputEvent);
	LookForKey(inputEvent);
	
}

void CoreInput::LookForKey(std::vector<InputEvent*>& inputEvent)
{
	HANDLEINPUT(ImGuiKey_Q)
	HANDLEINPUT(ImGuiKey_W)
	HANDLEINPUT(ImGuiKey_E)
	HANDLEINPUT(ImGuiKey_R)
	HANDLEINPUT(ImGuiKey_T)
	HANDLEINPUT(ImGuiKey_Y)
	HANDLEINPUT(ImGuiKey_U)
	HANDLEINPUT(ImGuiKey_I)
	HANDLEINPUT(ImGuiKey_O)
	HANDLEINPUT(ImGuiKey_P)
	HANDLEINPUT(ImGuiKey_A)
	HANDLEINPUT(ImGuiKey_S)
	HANDLEINPUT(ImGuiKey_D)
	HANDLEINPUT(ImGuiKey_F)
	HANDLEINPUT(ImGuiKey_G)
	HANDLEINPUT(ImGuiKey_H)
	HANDLEINPUT(ImGuiKey_J)
	HANDLEINPUT(ImGuiKey_K)
	HANDLEINPUT(ImGuiKey_L)
	HANDLEINPUT(ImGuiKey_Z)
	HANDLEINPUT(ImGuiKey_X)
	HANDLEINPUT(ImGuiKey_C)
	HANDLEINPUT(ImGuiKey_V)
	HANDLEINPUT(ImGuiKey_B)
	HANDLEINPUT(ImGuiKey_N)
	HANDLEINPUT(ImGuiKey_M)

}

void CoreInput::LookForMouse(std::vector<InputEvent*>& inputEvent)
{
	

	if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		inputEvent.push_back(new MouseLeftClick());
	}
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		inputEvent.push_back(new MouseRightClick());
	}

}


