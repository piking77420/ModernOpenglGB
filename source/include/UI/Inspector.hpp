#pragma once
#include "ImguiLayer.h"

class App;
class Project;

class Inspector : public ImguiLayer
{
public:
	void UpdateLayer(Project& currentProject) override;

	Inspector()
	{ 
		WindowName = "Inspector"; 
	}

	~Inspector() override
	{

	}
};

