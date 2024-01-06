#pragma once
#include<string>
#include "Core/Input/CoreInput.h"
class App;
class Project;

class ImguiLayer
{
public:
	
	std::string WindowName;
	virtual void UpdateLayer(Project& currentProject) {};
	virtual void RendererLayer(Project& currentProject) {};

	virtual ~ImguiLayer(){};
	bool IsFocus;

protected:
	virtual void ListenToInput(Project& currentProject,std::vector<InputEvent*>& inputEvent);
	bool Isopen = true;
};

