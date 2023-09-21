#pragma once
#include "ImguiLayer.h"
#include <vector>

class Entity;
class Transfrom;
class Project;

class Hierarchy : public ImguiLayer
{
public:

	void UpdateLayer(Project& currentProject, std::vector<InputEvent*>& inputsEvents);

	Hierarchy();
	 ~Hierarchy() override;
protected:
	void ListenToInput(Project& currentProject, std::vector<InputEvent*>& inputsEvents) override;

private:
	void ImguiDrawChildren(Entity* entity, Project& currentProject);
	void HierarchyMenue(Project& currentProject);
	bool hierackyMenue;
};

