#pragma once
#include "ImguiLayer.h"
#include "Core/ECS/Entity.h"
class App;
class Project;

class Inspector : public ImguiLayer
{
public:
	void UpdateLayer(Project& currentProject, std::vector<InputEvent*>& inputsEvents) override;


	Inspector()
	{ 
		WindowName = "Inspector"; 
	}

	~Inspector() override
	{

	}

protected:
	void ListenToInput(Project& currentProject, std::vector<InputEvent*>& inputEvent) override;
};

