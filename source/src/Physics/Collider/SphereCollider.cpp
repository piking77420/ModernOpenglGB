#include "Physics/Collider/SphereCollider.hpp"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>


void SphereCollider::ImguiWindowComponent()
{
	ImGui::Checkbox("IsDrawing", &collider.IsDrawing);
	ImGui::DragFloat("radius", &radius);


}
