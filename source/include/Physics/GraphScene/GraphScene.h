#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Core/Math/ToolBoxMathHeaders.h"
#include <thread>


class Transform;

class GraphScene : public IEcsSystem
{
public:


	ImplementIEcsSystem;


	static void BeChildOf(Transform* Parent, Transform* Child);
	static void NoParent(Transform* transform);
	static void UnChild(Transform* Parent, Transform* Child);

	GraphScene(){};
	 ~GraphScene() {};
private:



	const Matrix4X4 rootWorld = Matrix4X4::Identity();
	static Matrix4X4 ToMatrix(Transform* transform);

	void UpdateTransform(Transform* transform, uint32_t treeIndex);
	void StarTree(std::vector<Transform*>& transformVector);

	void GetParentLink(const Transform* transform, uint32_t& currentValue);
	uint32_t CountParentLink(const Transform* transform);
	void UpdateAllTransformPointers(std::vector<uint8_t>* data);

	static bool HasParent(const Transform* transform);
	static bool HasChild(const Transform* transform);


	static void UnbindParent(Transform* transform);
};

