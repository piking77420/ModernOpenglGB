#include "Collider/BoxCollider/BoxCollider.h"
#include "LowRenderer/RendererComponent/GizmoRenderer/Gizmo/Box/BoxGizmo.h"

void BoxCollider::Update(Scene* scene)
{

}

void BoxCollider::ImguiWindowComponents()
{
	ImGui::DragFloat3("Size", mSize.SetPtr());
	if (Gizmorenderer != nullptr)
		ImGui::Checkbox("Drawing", &Gizmorenderer->IsDrawing);	

}

BoxCollider::BoxCollider() : mSize(EntityAttachTo->transform.GetScale())
{
	m_ComponentName = "BOX COLLIDER";


	std::vector<Vector3> verticies;
	BoxGizmo* gizom = new BoxGizmo(*EntityAttachTo, mSize);
	Gizmorenderer = gizom;

	for (size_t i = 0; i < Gizmorenderer->m_Model->vertexVector.size(); i++)
	{
		verticies.push_back(Gizmorenderer->m_Model->vertexVector[i].Position);
	}
	AABCollision* type = new AABCollision(*EntityAttachTo, verticies, mSize);

	CollisionShape.push_back(type);
}

BoxCollider::BoxCollider(Vector3 size) :  mSize(size)
{
	m_ComponentName = "BOX COLLIDER";


	std::vector<Vector3> verticies;
	BoxGizmo* gizom = new BoxGizmo(*EntityAttachTo, mSize);
	Gizmorenderer = gizom;
		
	for (size_t i = 0; i < Gizmorenderer->m_Model->vertexVector.size(); i++)
	{
		verticies.push_back(Gizmorenderer->m_Model->vertexVector[i].Position);
	}
	AABCollision* type = new AABCollision(*EntityAttachTo, verticies, mSize);
	
	CollisionShape.push_back(type);
}

BoxCollider::~BoxCollider()
{
}


