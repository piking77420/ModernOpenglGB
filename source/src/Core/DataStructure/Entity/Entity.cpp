#include <Core/DataStructure/Entity/Entity.h>
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>
#include "App/App.h"
#include "Ressources/Scene/Scene.h"
#include "LowRenderer/Cam/Camera.h"

#include "Physics/Transform/Transform.h"
#include "External/ImguiGizmo/ImGuizmo.h"


void Entity::PreUpdate(Scene* scene)
{
	for (Component* c : Components)
	{
		c->PreUpdate(scene);
	}
}


void Entity::Awake(Scene* scene)
{
	for (Component* c : Components)
	{
		c->Awake(scene);
	}
}

void Entity::Start(Scene* scene)
{
	for (Component* c : Components)
	{
		c->Start(scene);
	}
}

void Entity::Update(Scene* scene)
{
	for(Component* c : Components)
	{
		c->Update(scene);
	}
}

void Entity::Renderer(Scene* scene)
{

}

void Entity::FixedUpdate(Scene* scene)
{
	for (Component* c : Components)
	{
		c->FixedUpdate(scene);
	}
}

void Entity::LateUpdate(Scene* scene)
{
	for (Component* c : Components)
	{
		c->LateUpdate(scene);
	}
}

void Entity::ImguiEntityWindow()
{


}

bool Entity::HasParent()
{
	if(transform.Parents != nullptr)
	{
		return true;
	}
	return false;
}

void Entity::OnSelected()
{
	ImGui::PushID(name.c_str());

	ImGui::CollapsingHeader(name.c_str(), NULL, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf);


	for (Component* c : Components)
	{

		c->ImguiWindow();
		ImGui::Text("");

	}
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Button Text").x) * 0.5f);

	if (ImGui::Button("AddComponent"))
	{
		if (ImGui::Button("MeshRenderer"))
		{
			AddComponent<MeshRenderer>();
		}

	}
	ImGui::PopID();


	/*






	static ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::ROTATE;
	static ImGuizmo::MODE currentGizmoMode = ImGuizmo::WORLD;

	if (ImGui::IsKeyPressed(ImGuiKey_1, false)) {
		currentGizmoOperation = ImGuizmo::TRANSLATE;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_2, false)) {
		currentGizmoOperation = ImGuizmo::ROTATE;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_3, false)) {
		currentGizmoOperation = ImGuizmo::SCALE;
	}
	if (ImGui::RadioButton("Translate", currentGizmoOperation == ImGuizmo::TRANSLATE)) {
		currentGizmoOperation = ImGuizmo::TRANSLATE;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", currentGizmoOperation == ImGuizmo::ROTATE)) {
		currentGizmoOperation = ImGuizmo::ROTATE;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", currentGizmoOperation == ImGuizmo::SCALE)) {
		currentGizmoOperation = ImGuizmo::SCALE;
	}

	if (currentGizmoOperation != ImGuizmo::SCALE) {
		if (ImGui::RadioButton("Local", currentGizmoMode == ImGuizmo::LOCAL)) {
			currentGizmoMode = ImGuizmo::LOCAL;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("World", currentGizmoMode == ImGuizmo::WORLD)) {
			currentGizmoMode = ImGuizmo::WORLD;
		}
	}
	else {
		currentGizmoMode = ImGuizmo::LOCAL;
	}



	Matrix4X4 modelMat = transform.GetMatrix();


	Matrix4X4 guizmoProj(Camera::cam->GetProjectionMatrix());
	


	ImGuiIO& io = ImGui::GetIO();

	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGuizmo::Manipulate(Camera::cam->GetLookMatrix().GetPtr(), guizmoProj.GetPtr(), currentGizmoOperation,
		currentGizmoMode, modelMat.SetPtr(), nullptr, nullptr);

	if(ImGuizmo::IsUsing())
	{
		Vector3 pos, rot, scale;

		ImGuizmo::DecomposeMatrixToComponents(modelMat.GetPtr(), pos.SetPtr(),
			rot.SetPtr(), scale.SetPtr());

		std::cout << rot << std::endl;
		Vector3 deltarotation = rot - transform.GetRotation();
	

		transform.SetPos() = pos;
		transform.SetRotation() += deltarotation;
		transform.SetScale() = scale;


	}
	*/
		
}











Entity::Entity(std::string _name,Scene* _scene) : name(_name) , transform(Transform(*this))
{
	this->AddComponent<Transform>(&transform);
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;
}

Entity::Entity(std::string _name, Transform _transform) :   name(_name), transform(_transform)
{
	this->AddComponent<Transform>(&transform);
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;
}

Entity::Entity() :  transform(Transform(*this))
{
	this->AddComponent<Transform>(&transform);
	this->m_ID = App::currentScene->GlobalID;
	App::currentScene->GlobalID++;

	this->name = "Entity " + std::to_string(m_ID);
}


Entity::~Entity()
{
	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i] = nullptr;
		delete Components[i];
		
	}
	

	Components.clear();
}




