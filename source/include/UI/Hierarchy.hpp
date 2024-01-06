#pragma once
#include "ImguiLayer.h"
#include <vector>

class Entity;
class Transfrom;
class Project;

class Hierarchy : public ImguiLayer
{
public:

	void UpdateLayer(Project& currentProject);

	Hierarchy();
	 ~Hierarchy() override;
	 

protected:

private:
	void ImguiDrawChildren(Entity* entity, Project& currentProject);
	void HierarchyMenue(Project& currentProject);
	bool hierackyMenue;
};

