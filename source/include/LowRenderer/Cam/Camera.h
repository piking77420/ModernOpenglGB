#pragma once

#include <Matrix4X4.h>
#include <Vector3.h>
#include <Vector4.h>
#include<Ressources/Shader/Shader.h>


#include"Ressources/RessourcesManager/RessourcesManager.h"



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
	void CameraRenderer(Shader* shader);
	void CameraGetInput(float xInput, float yInput);
	void CameraGetInput(Vector2 Input);

	Matrix4X4 GetTransform() const;

	static Camera* cam;

	static inline Camera* GetMainCamera()  
	{
		return cam;
	}


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

	Vector2 mouseSentivity = Vector2::One() * 0.5f;
	bool LeftClick;
	Vector2 mousePos;


	Matrix4X4 GetVp() 
	{
		return GetProjectionMatrix() * GetLookMatrix();
	}

	void CameraRotation();
	void CameraMovment();
private : 


	//Camera Shader
	float fov = 90;
	float Fnear = 0.01f;
	float Ffar = 1000.f;

};

