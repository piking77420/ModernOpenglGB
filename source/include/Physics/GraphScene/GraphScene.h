#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Core/Math/ToolBoxMathHeaders.h"
#include <thread>


class Transform;

class GraphScene : public IEcsSystem
{
public:
	void Update(Scene* scene) override;



	GraphScene(){};
	 ~GraphScene() override {};
private:
	void UpdateTransform(Transform* transform, uint32_t treeIndex);
	void StarTree(std::vector<Transform*>& transformVector);


	static Matrix4X4 ToMatrix(const Transform* transform);
	const Matrix4X4 rootWorld = Matrix4X4::Identity();

	void GetParentLink(const Transform* transform, uint32_t& currentValue);
	uint32_t CountParentLink(const Transform* transform);

};

