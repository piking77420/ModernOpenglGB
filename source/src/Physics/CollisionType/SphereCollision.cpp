#include "Physics/CollisionType/SphereCollision.h"
#include "Physics/PhysicsEngine.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include "Core/DataStructure/Component/Collider/SphereCollider/SphereCollider.h"
#include "Core/DataStructure/Component/Collider/PlaneCollider.h"





void SphereCollision::ImguiWindow()
{
	ImGui::PushID("");
	ImGui::DragFloat("Radius", &radius);	
	ImGui::PopID();
}




SphereCollision::~SphereCollision()
{
}

SphereCollision::SphereCollision(const Entity& currentObject, float& _radius) : CollisionType(currentObject) , radius(_radius)
{
}

