#include "Core/DataStructure/Component/Collider/Collider.h"
#include "Physics/CollisionType/CollisionType.h"



void Collider::DrawGizmo(Shader* shaderProgramm)
{
}

void Collider::PreUpdate(Scene* scene)
{
	

}

void Collider::Update(Scene* scene)
{
	for (size_t i = 0; i < CollisionShape.size(); i++)
	{
		CollisionShape[i]->Update(*this);
	}
	HasBeenCollided();
}

void Collider::ImguiWindowComponents()
{
	ImGui::Checkbox("Is Collided", &isCollided);
	if(Gizmorenderer != nullptr)
	ImGui::Checkbox("Drawing Gizmo", &Gizmorenderer->IsDrawing);
	for (size_t i = 0; i < CollisionShape.size(); i++)
	{
		ImGui::PushID("");
		CollisionShape[i]->ImguiWindow();
		ImGui::PopID();
	}

}

void Collider::HasBeenCollided()
{
	if (!entitesHasBeenCollid.empty())
	{
		isCollided = true;
		if(Gizmorenderer != nullptr)
		Gizmorenderer->color = Vector3(1, 0, 0);
	}
	else
	{
		if (Gizmorenderer != nullptr)
		Gizmorenderer->color = Vector3(1, 1, 1);

		isCollided = false;
	}
}

void Collider::LateUpdate(Scene* scene)
{
	entitesHasBeenCollid.clear();
}
