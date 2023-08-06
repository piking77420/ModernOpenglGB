#include "Physics/Transform/Transform.hpp"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>




void Transform::ImguiWindowComponent()
{
	ImGui::PushID("");

	// Pos
	ImGui::DragFloat3("Position", &pos.x, 0.2);

	// Angle
	ImGui::Text("Angle");
	ImGui::SliderAngle("X", &rotation.x);

	ImGui::SliderAngle("Y", &rotation.y);

	ImGui::SliderAngle("Z", &rotation.z);

	// Scale
	ImGui::DragFloat3("Scale", &scaling.x);


	ImGui::PopID();
}

Transform::Transform()
{
}

Transform::~Transform()
{
}