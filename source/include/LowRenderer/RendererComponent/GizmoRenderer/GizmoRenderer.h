#pragma once

#include "LowRenderer/RendererComponent/RendererComponent.h"
#include "Ressources/Model/Model.h"
#include "LowRenderer/Cam/Camera.h"

class Scene;


class GizmoRenderer : public RendererComponent
{
public:

	bool IsDrawing = true;
	Vector4 color;
	void ImguiWindowComponents() override;
	void Draw(Scene* scene, Shader* shader) override;
	GizmoRenderer(Entity& entityAttach);
	~GizmoRenderer();
	Model* m_Model;

protected:

};

