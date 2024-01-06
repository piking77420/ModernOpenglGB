#include <LowRenderer/Cam/Camera.h>
#include <Core/Debug/LogClass.h>
#include "App/App.h"
#ifndef SWIG

#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#endif // !SWIG

#include "Mathf.h"
#include "Core/DataStructure/Project.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "ECS/Scene.h"
#include "Core/Input/CoreInput.h"
#include "AppTime.h"

// Camera Init // 
float lastX = windowWidth / 2.0f;
float lastY = windowHeight / 2.0f;
bool firstmove = false;
Camera* Camera::cam = nullptr;//new Camera();


#ifndef SWIG

	bool IskeyPress(GLFWwindow* context, const int& GLFWInput)
	{
		if (glfwGetKey(context, GLFWInput) == GLFW_PRESS)
		{
			return true;
		}
		return false;
	}
#endif // !SWIG



Matrix4X4 Camera::GetLookMatrix() 
{
	
	return Matrix4X4::LookAt(eye, (eye + Front), Up);
}

Matrix4X4 Camera::GetProjectionMatrix() const
{
	return Matrix4X4::PerspectiveMatrix(Math::Deg2Rad * (fov), (float)Renderer::BindedFrameBuffer->widht/ (float)Renderer::BindedFrameBuffer->height, Fnear, Ffar);
}


#ifndef SWIG




#endif // !SWIG

	
void Camera::CameraRenderer(Shader* shader)
{
	shader->Use();
	Matrix4X4&& VP = GetProjectionMatrix() * GetLookMatrix();

	shader->SetMatrix("VP", VP.GetPtr());
	shader->SetMatrix("view", GetLookMatrix().GetPtr());
	shader->SetVector3("viewPos", &eye.x);
	shader->SetMatrix("projectionMatrix", GetProjectionMatrix().GetPtr());

}


#ifndef SWIG

void Camera::ImguiCameraWindow()
{
	if(ImGui::Begin("Camera"))
	{
		ImGui::DragFloat("CameraSpeed", &cameraVelocity);
		ImGui::DragFloat("FOV", &fov);
		ImGui::DragFloat3("Eye ", &eye.x);
		ImGui::End();
	}

}
#endif // !SWIG


Camera::Camera()
{
	
	eye = Vector3(0, 2, -8);

	cameraVelocity = 4;

	yaw = YAW;
	pitch = PITCH;

	Front = Vector3::Forward();
	Right = Vector3::Right();
	Up = Vector3::Up();

	CameraRotation();


}


Camera::~Camera()
{
}

void Camera::CameraGetInput(float xInput, float yInput)
{

	float xpos = static_cast<float>(xInput);
	float ypos = static_cast<float>(yInput);


	if (!firstmove)
	{
		lastX = xpos;
		lastY = ypos;
		firstmove = true;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;



	lastX = xpos;
	lastY = ypos;




	xoffset *= mouseSentivity.x;
	yoffset *= mouseSentivity.y;

	yaw += xoffset;
	pitch += yoffset;


	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	CameraRotation();
}

void Camera::CameraGetInput(Vector2 Input)
{
	CameraGetInput(Input.x, Input.y);
}

Matrix4X4 Camera::GetTransform() const
{
	return Matrix4X4::TRS(eye, Vector3(pitch, yaw, 0), Vector3::One());
}

void Camera::CameraRotation()
{
	
	Vector3 frontVector = Vector3::Zero();

	frontVector.x = std::cos(Math::Deg2Rad * yaw) * std::cos(Math::Deg2Rad * pitch);
	frontVector.y = std::sin(Math::Deg2Rad * pitch);
	frontVector.z = std::sin(Math::Deg2Rad * yaw) * std::cos(Math::Deg2Rad * pitch);

	Front = frontVector.Normalize();

	Right = Vector3::CrossProduct(Front,Vector3::Up()).Normalize();
	Up = Vector3::CrossProduct(Right,Front);
	
}



void Camera::CameraMovment()
{


	float addValue = cameraVelocity * AppTime::GetDeltatime();

	
	if (CoreInput::IsKeyHold(KEY_W))
	{
		eye += Front * addValue;
	}
	if (CoreInput::IsKeyHold(KEY_S))
	{
		eye -= Front * addValue;
	}
	if (CoreInput::IsKeyHold(KEY_A))
	{
		eye -= Right * addValue;
	}
	if (CoreInput::IsKeyHold(KEY_D))
	{
		eye += Right * addValue;
	}


	if (CoreInput::IsKeyHold(KEY_Space))
	{
		eye += Up * addValue;
	}
	if (CoreInput::IsKeyHold(KEY_LeftCtrl))
	{
		eye -= Up * addValue;
	}
	
	/*
	if (ImGui::IsKeyPressed(ImGuiKey_W,true))
	{
		eye += Front * addValue;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_S, true))
	{
		eye -= Front * addValue;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_A, true))
	{
		eye -= Right * addValue;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_D, true))
	{
		eye += Right * addValue;
	}


	if (ImGui::IsKeyPressed(ImGuiKey_Space, true))
	{
		eye += Up * addValue;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_LeftCtrl, true))
	{
		eye -= Up * addValue;
	}*/
}

