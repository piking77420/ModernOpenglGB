#include "Physics/Transform/Transform.hpp"

#ifndef SWIG

#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>
#endif 


#ifndef SWIG
void Transform::ImguiWindowComponent()
{
	Component::ImguiWindowComponent();

	ImGui::PushID("");

	// Pos
	ImGui::DragFloat3("Position", &pos.x, 0.2f);


	
	


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
		m_rotation = Quaternion::EulerAngle(rotationValue);
	}

	// Scale
	ImGui::DragFloat3("Scale", &scaling.x);


	ImGui::PopID();
}
#endif 

Transform::Transform()
{
}

Transform::~Transform()
{
}