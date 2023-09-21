#pragma once
#include<string>
#include "Core/Input/CoreInput.h"
class App;
class Project;

class ImguiLayer
{
public:
	
	std::string WindowName;
	virtual void UpdateLayer(Project& currentProject, std::vector<InputEvent*>& inputsEvents) {};

	virtual ~ImguiLayer(){};


protected:
	virtual void ListenToInput(Project& currentProject,std::vector<InputEvent*>& inputEvent) = 0;

};

