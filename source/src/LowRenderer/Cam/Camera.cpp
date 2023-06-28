#include <LowRenderer/Cam/Camera.h>
#include <Core/Debug/LogClass.h>
#include "App/App.h"
#include<Core/Debug/Imgui/imgui.h>
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>




// Camera Init // 
float lastX = windowWidth / 2.0f;
float lastY = windowHeight / 2.0f;
bool firstmove = false;
Camera* Camera::cam = new Camera();

bool IskeyPress(GLFWwindow* context , const int& GLFWInput )
{
	if(glfwGetKey(context, GLFWInput) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}



void Camera::SetCameraInfoForShaders(RessourcesManager& ressourcesManagers)
{
	std::map<std::string, IResource*>& mainMap = ressourcesManagers.GetRessources();

	for (auto it = mainMap.begin(); it != mainMap.end(); it++)
	{
		Shader* currentShader = dynamic_cast<Shader*>(it->second);
		if (currentShader != nullptr)
		{
			currentShader->Use();
			currentShader->SetMaxtrix("VP", this->VP.GetPtr());
			currentShader->SetMaxtrix("view", this->GetLookMatrix().GetPtr());
			currentShader->SetVector3("viewPos", &this->eye.x);

			currentShader->UnUse();

		}
	}
}

Matrix4X4 Camera::GetLookMatrix() 
{
	

	return Matrix4X4().LookAt(eye, eye + Front, Up);
}

Matrix4X4 Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}


	

void Camera::CameraUpdate() 
{

	  GLFWwindow* currentContext = glfwGetCurrentContext();
	  ImGuiIO& io = ImGui::GetIO();

	
	  CameraMovment(currentContext, io);
	  CameraRotation();


	  m_ProjectionMatrix = Matrix4X4::ProjectionMatrix((fov), (float)windowWidth / (float)windowHeight, Fnear, Ffar);

	  //m_ProjectionMatrix = Matrix4X4::OrthoGraphicMatrix(4,-4,4, -4, Fnear, Ffar).Transposate();
	  m_LookAtMatrix = GetLookMatrix();
	  VP =    m_ProjectionMatrix * m_LookAtMatrix;
	 
	
}


	
void Camera::CameraRenderer(Shader* shader)
{
	shader->Use();
	shader->SetMaxtrix("VP", VP.GetPtr());
	shader->SetMaxtrix("view", GetLookMatrix().GetPtr());
	shader->SetVector3("viewPos", &eye.x);
	shader->SetMaxtrix("projectionMatrix", GetProjectionMatrix().GetPtr());

}

void Camera::OnSelectObject(Shader* shader)
{
	//if(RigthClick)


}

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


Camera::Camera()
{
	
	eye = Vector3(0, 6, -15);

	cameraVelocity = 4;

	yaw = YAW;
	pitch = PITCH;

	Front = Vector3::Forward;
	Right = Vector3::Right;
	Up = Vector3::Up;

	CameraRotation();

	m_LookAtMatrix = GetLookMatrix();
	m_ProjectionMatrix = m_ProjectionMatrix.ProjectionMatrix((fov), (float)windowWidth / (float)windowHeight, Fnear, Ffar);

	VP = m_ProjectionMatrix * m_LookAtMatrix;
	mouseSentivity = CAMERASENSITIVITY;


}


Camera::~Camera()
{
}

void Camera::CameraGetInput(float xInput, float yInput)
{
	xInput *= mouseSentivity.x;
	yInput *= mouseSentivity.y;

	yaw += xInput;
	pitch += yInput;


	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	CameraRotation();
}

void Camera::CameraRotation()
{
	
	Vector3 frontVector = Vector3::Zero;

	frontVector.x = std::cos(degreesToRadians(yaw)) * std::cos(degreesToRadians(pitch));
	frontVector.y = std::sin(degreesToRadians(pitch));
	frontVector.z = std::sin(degreesToRadians(yaw)) * std::cos(degreesToRadians(pitch));

	Front = frontVector.Normalize();
	Right = Front.CrossProduct(Vector3::Up).Normalize();
	Up = Right.CrossProduct(Front);
	
}



void Camera::CameraMovment( GLFWwindow* context,const ImGuiIO& io )
{
	
	float velocity = cameraVelocity *  io.DeltaTime;

	if (IskeyPress(context, GLFW_KEY_W))
	{

		this->eye += Front * velocity;

	}
	else if (IskeyPress(context, GLFW_KEY_S))
	{
		this->eye -= Front * velocity;
	}


	if (IskeyPress(context, GLFW_KEY_A))
	{

		this->eye += Right * velocity;
	}
	else if (IskeyPress(context, GLFW_KEY_D))
	{

		this->eye -= Right * velocity;
	}

	if (IskeyPress(context, GLFW_KEY_SPACE))
	{
		this->eye += Up * velocity;
	}
	else if (IskeyPress(context, GLFW_KEY_LEFT_CONTROL))
	{
		this->eye -= Up * velocity;
	}
	
		
}
void Camera::MouseCallback(GLFWwindow* context, double _xpos, double _ypos)
{
	float xpos = static_cast<float>(_xpos);
	float ypos = static_cast<float>(_ypos);


	if (!firstmove)
	{
		lastX = xpos;
		lastY = ypos;
		firstmove = true;
	}

	float xoffset = lastX - xpos;
	float yoffset = lastY - ypos;



	lastX = xpos;
	lastY = ypos;

	if (glfwGetKey(context, GLFW_KEY_C) == GLFW_PRESS)
		Camera::cam->CameraGetInput(xoffset, yoffset);

}

void Camera::MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
	{
		Camera::cam->LeftClick = true;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		Camera::cam->mousePos.x = (float)x;
		Camera::cam->mousePos.y = (float)y;

	}

}
