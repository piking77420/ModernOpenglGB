#pragma once
#include "ImguiLayer.h"

class TransformGuizmo : public ImguiLayer
{
	std::string WindowName;
	void UpdateLayer(Project& currentProject) override;
	

	 ~TransformGuizmo() override{};
protected:
	void ListenToInput(std::vector<InputEvent*>& inputEvent);
};

