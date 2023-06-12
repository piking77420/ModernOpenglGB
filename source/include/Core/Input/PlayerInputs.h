#pragma once
#include "Ressources/RessourcesManager/RessourcesManager.h"


class App;


enum CurrentPlayerSceneState
{
	MENUE,LEVEL1
};

class PlayerInputs
{
public:
	void UpdatePlayerInput(App* app , RessourcesManager& managers);
	CurrentPlayerSceneState CurrentPlayerScene;
	PlayerInputs();
	~PlayerInputs();
private:
	GLFWwindow* context;
	void LoadLevel(App* app, RessourcesManager& managers);
	void LoadMenue(App* app, RessourcesManager& managers);
	void ChangeScene(App* app, RessourcesManager& managers);
	bool IskeyPress(const int& GLFWInput);
	CurrentPlayerSceneState PreviousCurrentPlayerScene;


};

