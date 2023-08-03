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
private:
	void ImguiDrawChildren(Entity* entity, Project& currentProject);
};

