#include "LowRenderer/Gizmo/Gizmo.hpp"
#include "Ressources/Shader/Shader.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "LowRenderer/Cam/Camera.h"

void Gizmo::InitGizmo(const Project& projet)
{

	Gizmo::Sphere = projet.ressourcesManager.GetElement<Model>("Sphere.obj");
	Gizmo::Box = projet.ressourcesManager.GetElement<Model>("cube.obj");
	Gizmo::GizmoShader = projet.ressourcesManager.GetElement<Shader>("GizmoShader");
}

void Gizmo::DrawSphere(const Vector3& pos, float radius, GizmoColor gizmoColor)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Gizmo::GizmoShader->Use();
	Matrix4X4 MVP = Camera::cam->GetProjectionMatrix() *  Camera::cam->GetLookMatrix() * Matrix4X4::TRS(pos, Vector3::Zero(), Vector3(radius, radius, radius));
	Vector4 color = Gizmo::GetColor(gizmoColor);
	
	GizmoShader->SetMatrix("MVP", MVP.GetPtr());
	GizmoShader->SetVector4("Color", color.GetPtr());

	Gizmo::Sphere->Draw();

	Gizmo::GizmoShader->UnUse();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}

void Gizmo::DrawBox(const Matrix4X4& model, const Vector3& sizeBox, GizmoColor gizmoColor)
{
	Vector3 pos, rotation, scale;

	Matrix4X4::DecomposeMatrix(model, pos, rotation, scale);


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Gizmo::GizmoShader->Use();
	Matrix4X4 MVP = Camera::cam->GetProjectionMatrix() * Camera::cam->GetLookMatrix() * Matrix4X4::TRS(pos, rotation, sizeBox);
	Vector4 color = Gizmo::GetColor(gizmoColor);

	GizmoShader->SetMatrix("MVP", MVP.GetPtr());
	GizmoShader->SetVector4("Color", color.GetPtr());

	Gizmo::Box->Draw();

	Gizmo::GizmoShader->UnUse();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}





