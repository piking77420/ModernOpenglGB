#pragma once
#include <vector>
#include "Core/ECS/ECSComponent.h"
#include "Core/Math/ToolBoxMathHeaders.h"
#include "Core/ECS/Entity.h"

class Transform : public EcsComponent<Transform>
{
public:
	
	Vector3 pos = Vector3::Zero();
	Vector3 rotation = Vector3::Zero();
	Vector3 scaling = Vector3::One();

	Matrix4X4 Local = Matrix4X4::Identity();
	Matrix4X4 World = Matrix4X4::Identity();


	// TO DO : Change pointers for entity ID beacause of the deallocation of the vector<uint_8> if you resize it 
	// the pointers will be invalud

	uint32_t ParentId = EntityNULL;
	const Transform* Parent = nullptr;
	std::vector <std::pair<uint32_t,Transform* >> childs;


	void ImguiWindowComponent() override;


	Transform();
	~Transform();

private:

};

