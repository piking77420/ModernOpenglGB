#pragma once
#include "Core/ECS/IECSSystem.h"
#include "Core/Math/ToolBoxMathHeaders.h"
#include "Core/ThreadPatern/ThreadPool.h"
#include "Core/ThreadPatern/ThreadPoolDynamic.h"

class Transform;


class GraphScene : public IEcsSystem
{
public:


	virtual void FixedUpdate(Scene* scene) override ;


	virtual void OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data) override ;
	



	static void BeChildOf(Transform* Parent, Transform* Child);
	static void NoParent(Transform* transform);
	static void UnChild(Transform* Parent, Transform* Child);


	static void GetParentLink(const Transform* transform, uint32_t& currentValue);
	static uint32_t CountParentLink(const Transform* transform);

	GraphScene(){};
	 ~GraphScene() {};
private:
	const Matrix4X4 m_rootWorld = Matrix4X4::Identity();

	static Matrix4X4 ToMatrix(Transform* transform);

	void UpdateTransform(Transform* transform, uint32_t treeIndex);
	void StarTree(std::vector<Transform>* transformVector , std::uint32_t entityToAvoid);

	void UpdateAllTransformPointers(std::vector<uint8_t>* data);

	static bool HasParent(const Transform* transform);
	static bool HasChild(const Transform* transform);
		
	static void UnbindParent(Transform* transform);

	static void UpdateWorld(Transform* transform);
	static void ThreadUpdateTranform(std::vector<Transform>* transformVector,uint32_t startIndex, uint32_t endIndex);

	static Matrix4X4 ReturnParentsMatrix(const Transform* parent);

};

