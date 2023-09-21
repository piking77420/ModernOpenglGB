#pragma once

#include <Matrix4X4.h>
#include <Vector3.h>
#include <Vector4.h>
#include<Ressources/Shader/Shader.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include"Ressources/RessourcesManager/RessourcesManager.h"

const Vector2 CAMERASENSITIVITY = Vector2(0.2f, 0.2f);


// Default Camera Value // 
const float YAW = 90.f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
///////////////////


class Camera
{
public:

	
	Matrix4X4 GetLookMatrix();
	Matrix4X4 GetProjectionMatrix() const;
	void ImguiCameraWindow();
	void CameraUpdate();
	void CameraRenderer(Shader* shader);
	void CameraGetInput(float xInput, float yInput);
	Matrix4X4 GetTransform() const;

	static Camera* cam;
	static void MouseCallback(GLFWwindow* context, double _xpos, double _ypos);
	static void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);

	Camera();
	~Camera();

	// Camera Pos // 
	Vector3 eye;
	Vector3 Front;
	Vector3 Up;

	Vector3 Right;
	float pitch;
	float yaw;
	float cameraVelocity;

	// CameraControl

	Vector2 mouseSentivity;
	bool LeftClick;
	Vector2 mousePos;


	Matrix4X4 GetVp() 
	{
		return GetProjectionMatrix() * GetLookMatrix();
	}

private : 
	void CameraRotation();
	void CameraMovment(GLFWwindow* context, const ImGuiIO& io);

	//Camera Shader
	float fov = 85.f;
	float Fnear = 0.01f;
	float Ffar = 1000.f;
	Matrix4X4 VP;
	Matrix4X4 m_LookAtMatrix;
	Matrix4X4 m_ProjectionMatrix;
};

