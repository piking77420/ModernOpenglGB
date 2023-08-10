#include "Physics/Collider/BoxCollider.hpp"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>

void BoxCollider::ImguiWindowComponent()
{
	ImGui::Text("BOX COLLIDER \n ");

	ImGui::Text("CollisionPoint size = %d ", collider.CollisionPoint.size());
	ImGui::Checkbox("IsDrawing", &collider.IsDrawing);
	ImGui::DragFloat3("BoxSize", Size.SetPtr());
}
BoxCollider::BoxCollider()
{
	collider.collisionType = CollisionType::Box;
}

BoxCollider::~BoxCollider()
{
}

;