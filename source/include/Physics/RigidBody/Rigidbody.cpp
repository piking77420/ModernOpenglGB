#include "Rigidbody.h"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>
void Rigidbody::ImguiWindowComponent()
{

	ImGui::Text("RigidBody");


	ImGui::Checkbox("IsKinematic", &IsKinematic);
	if(ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Turn off / on is the object is kinematic ");
	}

	ImGui::Checkbox("IsGavityApllie", &IsGravityApplie);
	ImGui::DragFloat("Mass ", &mass);
	ImGui::DragFloat("dragCoeff ", &drag,0.01f, 0.99f);
	ImGui::Text("Force: %.3f, %.3f, %.3f", Force.x, Force.y, Force.z);
	ImGui::Text("Velocity: %.3f, %.3f, %.3f", Velocity.x, Velocity.y, Velocity.z);
	
}
