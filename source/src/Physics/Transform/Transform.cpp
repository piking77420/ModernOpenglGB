#include "Physics/Transform/Transform.h"


int Transform::TransformGlobalID = 0;





void Transform::SetParent(Transform& parents)
{
	this->Parents = &parents;
	parents.AddChildren(this);
}

void Transform::AddChildren(Transform* Childs)
{
	this->Childrens.push_back(Childs);
}

void Transform::ImguiWindowComponents()
{
	ImGui::PushID("");

	ImGui::DragFloat3("Position", &pos.x,0.2);

	ImGui::Text("Angle");
	ImGui::SliderAngle("X", &rotate.x);
	ImGui::SliderAngle("Y", &rotate.y);
	ImGui::SliderAngle("Z", &rotate.z);

	ImGui::DragFloat3("Scale", &scale.x);
	ImGui::PopID();

}

Matrix4X4& Transform::SetMatrix() 
{
	return m_LocalMatrix;
}

const Matrix4X4& Transform::GetMatrix() const 
{
	return m_GlobalMatrix;
}

const Matrix4X4& Transform::GetLocal() const
{
	return m_LocalMatrix;
}

const Vector3 Transform::GetWordlPos() const
{
	Vector3 result = Vector3(m_GlobalMatrix.Columns[3].x, m_GlobalMatrix.Columns[3].y, m_GlobalMatrix.Columns[3].z);
	return result;
}
const Vector3 Transform::GetWordlPos()
{
	return Vector3(m_GlobalMatrix.Columns[3]);
}


void Transform::Update(Scene* scene)
{ 
	UpdateMatrix();
}

Transform::Transform(Entity& currentObject,const Vector3& _pos, const Vector3& _rotation, const Vector3& _scaling) : pos(_pos), rotate(_rotation), scale(_scaling) 
{
	UpdateMatrix();
	IdTransform = TransformGlobalID;
	TransformGlobalID++;
}

Transform::Transform(Entity& currentObject) 
{
	m_ComponentName = "Transform";
	pos = Vector3::Zero;
	scale = Vector3::One;
	rotate = Vector3::Zero;
	m_LocalMatrix = Matrix4X4().Identity();
	m_GlobalMatrix = m_LocalMatrix;

	IdTransform = TransformGlobalID;
	TransformGlobalID++;


}
Transform::~Transform()
{
}

void Transform::UpdateMatrix()
{
	
	m_LocalMatrix = m_LocalMatrix.TRS(pos, rotate, scale);

	if (Parents != nullptr)
	{
		m_GlobalMatrix = Parents->GetMatrix() * m_LocalMatrix;
	}
	else
	{
		m_GlobalMatrix =  m_LocalMatrix;
	}


}
