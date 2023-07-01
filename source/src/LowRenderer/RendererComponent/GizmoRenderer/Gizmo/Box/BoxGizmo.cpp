#include "LowRenderer/RendererComponent/GizmoRenderer/Gizmo/Box/BoxGizmo.h"
#include "Ressources/Scene/Scene.h"
BoxGizmo::~BoxGizmo()
{

}


void BoxGizmo::Draw(Scene* scene, Shader* shader)
{


	if (!IsDrawing || !IsEnabled )
		return;

	 

	shader->Use();

	shader->SetVector4("Color", color.GetPtr());
	

	Matrix4X4 model =  Matrix4X4().TRS(EntityAttachTo->transform.GetWordlPos(), EntityAttachTo->transform.GetRotation(), Size);
	Matrix4X4 MVP = scene->cam->GetProjectionMatrix() * scene->cam->GetLookMatrix() * model;
	shader->SetMaxtrix("model ", model.GetPtr());




	shader->SetMaxtrix("MVP", MVP.GetPtr());
	shader->SetMaxtrix("rotation", Matrix4X4().RotationMatrix4X4(EntityAttachTo->transform.GetRotation()).GetPtr());
	// Draw The Object
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE_STRIP);
	m_Model->Draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

BoxGizmo::BoxGizmo(Entity& entityAttach, Vector3& size) : GizmoRenderer(entityAttach) , Size(size)
{
	m_Model = GizmoRenderer::ressourcesManager->GetElement<Model>("cube.obj");

}
