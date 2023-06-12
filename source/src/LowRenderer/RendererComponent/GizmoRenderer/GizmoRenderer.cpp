#include "LowRenderer/RendererComponent/GizmoRenderer/GizmoRenderer.h"
#include "Ressources/RessourcesManager/RessourcesManager.h"
#include "Ressources/Scene/Scene.h"

void GizmoRenderer::ImguiWindowComponents()
{
}

void GizmoRenderer::Draw(Scene* scene, Shader* shader)
{

	if (!IsDrawing)
		return;

	shader->Use();
	
	shader->SetVector4("Color", color.GetPtr());

	Matrix4X4 model = EntityAttachTo.transform.m_GlobalMatrix;
	Matrix4X4 MVP = scene->cam->GetProjectionMatrix() * scene->cam->GetLookMatrix() * model;
	shader->SetMaxtrix("model ", model.GetPtr());

	shader->SetMaxtrix("MVP", MVP.GetPtr());
	shader->SetMaxtrix("rotation", Matrix4X4().RotationMatrix4X4(EntityAttachTo.transform.rotate).GetPtr());
	// Draw The Object
  	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE_STRIP);
	m_Model->Draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
}


GizmoRenderer::GizmoRenderer(Entity& entityAttach) : RendererComponent(entityAttach)
{
	
	color = Vector4::One;
}


GizmoRenderer::~GizmoRenderer()
{

}
