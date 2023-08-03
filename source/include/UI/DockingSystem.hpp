#pragma once
#include "ImguiLayer.h"
#include <vector>
#include "UI/InspectorSelectable.h"

class App;
class Project;

class DockingSystem
{
public:
	void UpdateDockSpace(Project& CurrentProject);

	InspectorSelectable* Insepctor;
	DockingSystem();

private:
	std::vector<ImguiLayer*> ImguiLayers;

};

