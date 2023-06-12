#include "Core/Input/PlayerInputs.h"
#include "Ressources/Scene/Scene.h"
#include"External/GLFW/glfw3.h"

#include "App/App.h"



bool PlayerInputs::IskeyPress(const int& GLFWInput)
{
	if (ImGui::IsKeyReleased(ImGuiKey_E))
	{
		return true;
	}
	return false;
}


void PlayerInputs::UpdatePlayerInput(App* app, RessourcesManager& managers)
{
	context = glfwGetCurrentContext();
	LoadLevel(app, managers);
	LoadMenue(app, managers);
	ChangeScene(app, managers);
}	

PlayerInputs::PlayerInputs()
{
	CurrentPlayerScene = LEVEL1;
	PreviousCurrentPlayerScene = LEVEL1;
	context = glfwGetCurrentContext();

}

PlayerInputs::~PlayerInputs()
{

}

void PlayerInputs::LoadLevel(App* app, RessourcesManager& managers)
{
	if(IskeyPress(GLFW_KEY_E))
	{
		// POP Menue;
		PreviousCurrentPlayerScene = LEVEL1;
	}


	if(IskeyPress(GLFW_KEY_UP))
	{

	}
	else if (IskeyPress(GLFW_KEY_DOWN))
	{

	}
	else if (IskeyPress(GLFW_KEY_RIGHT))
	{

	}
	else if (IskeyPress(GLFW_KEY_LEFT))
	{

	}

}

void PlayerInputs::LoadMenue(App* app, RessourcesManager& managers)
{
	if (ImGui::IsKeyReleased(ImGuiKey_E))
	{
		ChangeScene(app, managers);
	}
	
}

void PlayerInputs::ChangeScene(App* app, RessourcesManager& managers)
{	
	if(CurrentPlayerScene != PreviousCurrentPlayerScene)
	{
		switch (CurrentPlayerScene)
		{
		case MENUE:
			PreviousCurrentPlayerScene = MENUE;
			app->currentScene = managers.GetElement<Scene>("Menue");
			break;
		case LEVEL1:
			PreviousCurrentPlayerScene = LEVEL1;
			app->currentScene = managers.GetElement<Scene>("Level1");
			break;
		default:
			break;
		}
		

		if (CurrentPlayerScene == LEVEL1)
		{
			CurrentPlayerScene = MENUE;
		}
		else if (CurrentPlayerScene == MENUE)
		{
			CurrentPlayerScene = LEVEL1;
		}
	}
	

}
