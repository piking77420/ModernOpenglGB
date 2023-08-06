#pragma once
#include "ImguiLayer.h"

class TransformGuizmo : public ImguiLayer
{
	std::string WindowName;
	void UpdateLayer(Project& currentProject) override;
	

	 ~TransformGuizmo() override{};

};

