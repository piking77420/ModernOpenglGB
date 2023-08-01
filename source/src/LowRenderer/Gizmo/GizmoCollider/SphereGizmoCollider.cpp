#include "LowRenderer/Gizmo/GizmoCollider/SphereGizmoCollider.h"
#include "Ressources/Shader/Shader.h"
#include "Ressources/Scene/Scene.h"
#include "App/App.h"
#include "LowRenderer/Cam/Camera.h"
#include <vector>

#include "Vector4.h"



void SphereGizmoCollider::Render(Shader* shaderProgramm, Scene* scene)
{
	/*
	if (*transformEntity == nullptr)
		return;

	const Entity* e = *transformEntity;
	const Transform* transform = &e->transform;


	Matrix4X4 test = Matrix4X4::TRS(Vector3::Zero(), Vector3::Zero(), Vector3(*radius, *radius, *radius));


	shaderProgramm->Use();

	shaderProgramm->SetVector4("Color", color.GetPtr());
	Matrix4X4 modelMatrix = transform->m_GlobalMatrix * test;
	Matrix4X4 MVP = scene->cam->GetProjectionMatrix() * scene->cam->GetLookMatrix() * modelMatrix;
	shaderProgramm->SetMaxtrix("modelMatrix ", modelMatrix.GetPtr());

	shaderProgramm->SetMaxtrix("MVP", MVP.GetPtr());
	shaderProgramm->SetMaxtrix("rotation", Matrix4X4().RotationMatrix4X4(transform->GetRotation()).GetPtr());
	// Draw The Object
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	model->Draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
}

SphereGizmoCollider::~SphereGizmoCollider()
{
}
