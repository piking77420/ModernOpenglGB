#pragma once
#include "LowRenderer/Gizmo/Gizmo.h"



class SphereGizmoCollider : public Gizmo
{
public:

	void Render(Shader* shaderProgramm, Scene* scene) override;

	float* radius;
	SphereGizmoCollider();
	~SphereGizmoCollider();

private:

};

