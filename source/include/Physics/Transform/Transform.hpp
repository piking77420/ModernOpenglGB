#pragma once
#include <vector>
#include "Core/ECS/ECSComponent.h"
#include "Core/Math/ToolBoxMathHeaders.h"


class Transform : public EcsComponent<Transform>
{
public:
	
	Vector3 pos;
	Vector3 rotation;
	Vector3 scaling;

	Matrix4X4 Local = Matrix4X4::Identity();
	Matrix4X4 World = Matrix4X4::Identity();

	const Transform* Parent = nullptr;
	std::vector<Transform*> childs;
	void ImguiWindowComponent() override;


	Transform();
	~Transform();

private:

};

