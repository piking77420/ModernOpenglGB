#include "UI/SceneView.h"
#include "App/App.h"
#include "Renderer/Renderer.hpp"
#include "External/ImguiGizmo/ImGuizmo.h"
#include <UI/Hierarchy.hpp>
#include "Physics/Transform/Transform.hpp"


void SceneView::ResizeBuffer(int widht, int heignt)
{
	glViewport(0, 0, widht, heignt);
	m_SceneBuffer.ResizeFrammeBuffer((float)widht, (float)heignt);
}


void SceneView::BindSceneView()
{
	Camera::cam = &m_cam;
	Renderer::BindedFrameBuffer = &m_SceneBuffer;

	glViewport(0, 0, m_SceneBuffer.widht, m_SceneBuffer.height);
}

void SceneView::UpdateLayer(Project& currentProject)
{
	

}

void SceneView::RendererLayer(Project& currentProject)
{
	Shader* shader = ResourcesManager::GetElement<Shader>("AAShader");


	if (sceneViewEnum == SceneViewEnum::EDITOR)
	{
		WindowName = "EDITOR";
	}

	if (sceneViewEnum == SceneViewEnum::GAME)
	{
		WindowName = "GAME";
	}

	


	ImGui::Begin(WindowName.c_str(), &Isopen);
	
	IsFocus = ImGui::IsWindowFocused();


	

		if (IsFocus)
		{

			m_cam.CameraMovment();
			// TO DO Refactor this 
			if (CoreInput::IsKeyHold(MOUSE_Right))
			{
				ImVec2 windowPos = ImGui::GetWindowPos();
				ImVec2 windowSize = ImGui::GetWindowSize();

				// Calculate the center of the window
				float centerX = windowPos.x + (0.5f * windowSize.x);
				float centerY = windowPos.y + (0.5f * windowSize.y);

				Vector2 cursorpos = CoreInput::GetMousePos();
				cursorpos -= {windowWidth, windowHeight};


				m_cam.CameraGetInput(cursorpos + Vector2(centerX, centerY));
			}
		}

		Gizmo(currentProject);

		

		
		m_SceneBuffer.BlitBuffers();
		
		ImGui::Image((ImTextureID)m_SceneBuffer.screenTexture, ImGui::GetContentRegionAvail(),
				ImVec2(0, 1),
				ImVec2(1, 0));
		
		
		/*ImGui::Image((ImTextureID)m_SceneBuffer.framebufferTexture, ImGui::GetContentRegionAvail(),
				ImVec2(0, 1),
				ImVec2(1, 0));
		*/





		ImGui::End();
	
}



void SceneView::Gizmo(Project& currentProject)
{
	return;

	ImguiLayer* layer = currentProject.dockingSystem.GetLayer<Hierarchy>();


	if ((!IsFocus && !layer->IsFocus))
	{

		if (currentProject.dockingSystem.EnitySelectedID != EntityNULL)
		{
			Entity* ent = currentProject.currentScene->GetEntities(currentProject.dockingSystem.EnitySelectedID);
			Transform* ptr = currentProject.currentScene->GetComponent<Transform>(ent);

			Matrix4X4::DecomposeMatrix(ptr->world, ptr->pos, ptr->rotationValue, ptr->scaling);
		}

		return;
	}

	if (currentProject.dockingSystem.EnitySelectedID == EntityNULL)
	{
		return;
	}


	if (!IsFocus)
	{
		return;
	}


	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();

	float windowWidht = (float)ImGui::GetWindowWidth();
	float windowHeight = (float)ImGui::GetWindowHeight();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidht, windowHeight);

	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);

	if (ImGui::IsKeyPressed(ImGuiKey_R))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(ImGuiKey_T))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(ImGuiKey_Y))
		mCurrentGizmoOperation = ImGuizmo::SCALE;





	//Camera
	Camera& cam = *Camera::cam;
	const Matrix4X4& projection = cam.GetProjectionMatrix();
	Matrix4X4 camerview = cam.GetLookMatrix();

	uint32_t entityId = currentProject.dockingSystem.EnitySelectedID;
	Transform* transform = currentProject.currentScene->GetComponent<Transform>(currentProject.currentScene->GetEntities(entityId));


	ImGuizmo::Manipulate(camerview.GetPtr(), projection.GetPtr(), mCurrentGizmoOperation, ImGuizmo::LOCAL, transform->world.SetPtr());


}

SceneView::SceneView()
{
}

SceneView::~SceneView()
{
}