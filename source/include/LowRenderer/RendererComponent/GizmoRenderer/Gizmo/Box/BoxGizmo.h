#pragma once
#include"LowRenderer/RendererComponent/GizmoRenderer/GizmoRenderer.h"

class BoxGizmo : public GizmoRenderer
{
public:
	Vector3& Size;

	void Draw(Scene* scene, Shader* shader);

	BoxGizmo(Entity& entityAttach , Vector3& size);
	~BoxGizmo();
};

