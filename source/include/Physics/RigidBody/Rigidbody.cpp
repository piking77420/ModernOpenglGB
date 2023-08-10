#include "Rigidbody.h"
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>
void Rigidbody::ImguiWindowComponent()
{
	ImGui::Text("RigidBody");
	ImGui::Text("");
	ImGui::Checkbox("IsKinematic", &IsKinematic);
	ImGui::Checkbox("IsGavityApllie", &IsGravityApplie);
	ImGui::DragFloat("Mass ", &mass);
	ImGui::Text("Force: %.2f, %.2f, %.2f", Force.x, Force.y, Force.z);
	ImGui::Text("Velocity: %.2f, %.2f, %.2f", Velocity.x, Velocity.y, Velocity.z);
	
}
