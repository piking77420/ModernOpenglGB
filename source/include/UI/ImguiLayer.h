#pragma once
#include<string>

class App;
class Project;

class ImguiLayer
{
public:
	
	std::string WindowName;
	virtual void UpdateLayer(Project& currentProject){};

	virtual ~ImguiLayer(){};

private:

};

