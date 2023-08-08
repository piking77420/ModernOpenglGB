#include "Physics/Collider/BoxCollider.hpp"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>

void BoxCollider::ImguiWindowComponent()
{
	ImGui::Checkbox("IsDrawing", &collider.IsDrawing);
	ImGui::DragFloat3("BoxSize", Size.SetPtr());
};