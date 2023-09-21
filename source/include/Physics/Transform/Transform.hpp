#pragma once
#include <vector>
#include "Core/ECS/ECSComponent.h"
#include "Core/Math/ToolBoxMathHeaders.h"
#include "Core/ECS/Entity.h"

class GraphScene;


class Transform : public EcsComponent<Transform>
{
public:
	
	Vector3 pos = Vector3::Zero();
	Vector3 scaling = Vector3::One();
	Vector3 rotationValue;
	Matrix4X4 local = Matrix4X4::Identity();
	Matrix4X4 world = Matrix4X4::Identity();


	void SetRotation(const Quaternion& q) 
	{ 
		m_rotation = q;
		rotationValue = m_rotation.ToEulerAngle();
	};


	// In Radians
	void SetRotation(const Vector3& eulerangle)
	{ 
		m_rotation = Quaternion::EulerAngle(eulerangle);
		rotationValue = eulerangle * Math::Rad2Deg;
	};

	const Quaternion& GetRotation() const { return m_rotation; };

	uint32_t parentID = EntityNULL;
	const Transform* parent = nullptr;
	std::vector <std::pair<uint32_t,Transform* >> childs;


	void ImguiWindowComponent() override;

	Transform();
	~Transform();

private:
	Quaternion m_rotation;
	friend GraphScene;
};

