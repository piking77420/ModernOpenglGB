#pragma once
#include"LowRenderer/RendererComponent/GizmoRenderer/GizmoRenderer.h"



class SphereGizmo : public GizmoRenderer
{
public:
	float& radius;

	void Draw(Scene* scene, Shader* shader) override;

	SphereGizmo(Entity& entityAttach,float& _radius);

	~SphereGizmo();
};

