#include "Physics/Transform/Transform.hpp"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>




void Transform::ImguiWindowComponent()
{
	Component::ImguiWindowComponent();

	ImGui::PushID("");

	// Pos
	ImGui::DragFloat3("Position", &pos.x, 0.2);


	
	


	// Angle
	ImGui::Text("Angle");
	ImGui::DragFloat("X", &rotationValue.x);
	bool x = ImGui::IsItemEdited();
	ImGui::DragFloat("Y", &rotationValue.y);
	bool y = ImGui::IsItemEdited();
	ImGui::DragFloat("Z", &rotationValue.z);
	bool z = ImGui::IsItemEdited();

	if(x || y || z)
	{
		rotation = Quaternion::EulerAngle(rotationValue);
	}

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