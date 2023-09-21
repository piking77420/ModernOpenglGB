#pragma once
#include "ImguiLayer.h"

class TransformGuizmo : public ImguiLayer
{
	std::string WindowName;
	void UpdateLayer(Project& currentProject, std::vector<InputEvent*>& inputsEvents) override;
	

	 ~TransformGuizmo() override{};
protected:
	void ListenToInput(std::vector<InputEvent*>& inputEvent);
};

