#include "LowRenderer/RendererComponent/GizmoRenderer/Gizmo/Sphere/SphereGizmo.h"
#include "Ressources/Scene/Scene.h"
#include "Collider/SphereCollider/SphereCollider.h"





void SphereGizmo::Draw(Scene* scene, Shader* shader)
{


	if (!IsDrawing)
		return;

	shader->Use();

	shader->SetVector4("Color", color.GetPtr());

	Matrix4X4 model = Matrix4X4().TRS(EntityAttachTo->transform.GetWordlPos(), EntityAttachTo->transform.GetRotation(),Vector3(radius, radius, radius));
	Matrix4X4 MVP = scene->cam->GetProjectionMatrix() * scene->cam->GetLookMatrix() * model;
	shader->SetMaxtrix("model ", model.GetPtr());

	shader->SetMaxtrix("MVP", MVP.GetPtr());
	shader->SetMaxtrix("rotation", Matrix4X4().RotationMatrix4X4(EntityAttachTo->transform.GetRotation()).GetPtr());
	// Draw The Object
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_Model->Draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


SphereGizmo::SphereGizmo(Entity& entityAttach,float& _radius) : GizmoRenderer(entityAttach), radius(_radius)
{
	
	m_Model = RendererComponent::ressourcesManager->GetElement<Model>("Sphere.obj");

}
SphereGizmo::~SphereGizmo()
{
}