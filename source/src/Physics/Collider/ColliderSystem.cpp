#include <Core/CoreEngine.h>
#include <ToolBoxMathHeaders.h>
#include "Physics/Raycast/Raycast.h"
#include "Vector4.h"
#include "Physics/Collider/ColliderSystem.hpp"
#include "Physics/Collider/SphereCollider.hpp"
#include "Physics/Collider/BoxCollider.hpp"
#include "ECS/Scene/Scene.h"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/Gizmo/Gizmo.hpp"
#include "Physics/Raycast/Raycast.h"


void ColliderSystem::Init(Scene* scene)
{
	m_currentScene = scene;

}

void ColliderSystem::Awake(Scene* scene)
{
	m_currentScene = scene;
}

void ColliderSystem::Start(Scene* scene)
{

}



void ColliderSystem::OnDrawGizmo(Scene* scene)
{
	std::vector<SphereCollider>* dataSphere = reinterpret_cast<std::vector<SphereCollider>*>(scene->GetComponentDataArray<SphereCollider>());

	for (size_t i = 0; i < dataSphere->size(); i++)
	{
		SphereCollider* sphereptr = &(*dataSphere)[i];
		if(sphereptr->collider.IsDrawing)
		{
			Transform* transform = scene->GetComponent<Transform>(scene->GetEntities( sphereptr->entityID));
			Vector3 transformPos = transform->world.GetPos();
			Gizmo::DrawSphere(transformPos, sphereptr->radius,GizmoColor::GREENGIZMO);

		}
	}


	std::vector<BoxCollider>* boxData = reinterpret_cast<std::vector<BoxCollider>*>(scene->GetComponentDataArray<BoxCollider>());

	for (size_t i = 0; i < boxData->size(); i++)
	{
		BoxCollider* boxptr= &(*boxData)[i];
		if (boxptr->collider.IsDrawing)
		{
			Transform* transform = scene->GetComponent<Transform>(scene->GetEntities(boxptr->entityID));
			Vector3 transformPos = transform->world.GetPos();
			Gizmo::DrawBox(transform->world, boxptr->Size, GizmoColor::GREENGIZMO);

		}
	}



}



void ColliderSystem::ProcessSphereSphere(std::vector<SphereCollider>* sphereData)
{
	

	for (size_t i = 0; i < sphereData->size(); i++)
	{
		SphereCollider* sphereptr = &(*sphereData)[i];
		for (size_t k = i + 1; k < sphereData->size(); k++)
		{
			SphereCollider* sphereptr2 = &(*sphereData)[k];
			if (sphereptr == sphereptr2)
				continue;
			
			ColliderSystem::CheckCollisionSphereSphere( *sphereptr, *sphereptr2);

		}
	}

}

void ColliderSystem::ProcessBoxBox(std::vector<BoxCollider>* boxData)
{
	for (size_t i = 0; i < boxData->size(); i++)
	{
		BoxCollider* Boxptr = &(*boxData)[i];
		for (size_t k =  i + 1; k < boxData->size(); k++)
		{
			BoxCollider* Boxptr2 = &(*boxData)[k];
			if (Boxptr == Boxptr2)
				continue;


			ColliderSystem::CheckCollisionBoxBox( *Boxptr, *Boxptr2);

		}
	}
}

void ColliderSystem::ProcessSphereBox(std::vector<SphereCollider>* sphereData, std::vector<BoxCollider>* boxData)
{
	for (size_t i = 0; i < sphereData->size(); i++)
	{
		SphereCollider* sphereptr = &(*sphereData)[i];

		for (size_t k = i + 1; k < boxData->size(); k++)
		{
			BoxCollider* Boxptr = &(*boxData)[i];
	
			ColliderSystem::CheckCollisionBoxSphere( *Boxptr, *sphereptr);

		}
	}
}

void ColliderSystem::FixedUpdate(Scene* scene)
{
	std::vector<SphereCollider>* dataSphere =  reinterpret_cast<std::vector<SphereCollider>*>(scene->GetComponentDataArray<SphereCollider>());
	std::vector<BoxCollider>* dataBox = reinterpret_cast<std::vector<BoxCollider>*>(scene->GetComponentDataArray<BoxCollider>());


	ProcessSphereSphere(dataSphere);
	
	ProcessBoxBox(dataBox);

	ProcessSphereBox(dataSphere, dataBox);

	


}



void ColliderSystem::Update(Scene* scene)
{
}



void ColliderSystem::LateUpdate(Scene* scene)
{

	std::vector<SphereCollider>* dataSphere = reinterpret_cast<std::vector<SphereCollider>*>(scene->GetComponentDataArray<SphereCollider>());
	std::vector<BoxCollider>* dataBox = reinterpret_cast<std::vector<BoxCollider>*>(scene->GetComponentDataArray<BoxCollider>());

	

	for (size_t i = 0; i < dataSphere->size(); i++)
	{
		SphereCollider* sphereptr = &(*dataSphere)[i];
		sphereptr->collider.CollisionPoint.clear();
	}
	for (size_t i = 0; i < dataBox->size(); i++)
	{
		BoxCollider* Boxreptr = &(*dataBox)[i];
		Boxreptr->collider.CollisionPoint.clear();
	}
}

void ColliderSystem::Render(Shader& shader, Scene* scene)
{


}

void ColliderSystem::OnResizeData(uint32_t ComponentTypeID, std::vector<uint8_t>* data)
{


}



void ColliderSystem::CheckCollisionSphereSphere(SphereCollider& sphere1, SphereCollider& sphere2)
{
	 Entity* entityID1 = m_currentScene->GetEntities(sphere1.entityID);
	 Entity* entityID2 = m_currentScene->GetEntities(sphere2.entityID);

	const Transform* s1 = m_currentScene->GetComponent<Transform>(entityID1);
	const Transform* s2 = m_currentScene->GetComponent<Transform>(entityID2);

	const Vector3 worldPosS1 = static_cast<const Vector3>(s1->world[3]);
	const Vector3 worldPosS2 = static_cast<const Vector3>(s2->world[3]);

	const float Distance = Vector3::Distance(worldPosS1, worldPosS2);
	const float r1r2 = sphere1.radius + sphere2.radius;


	if (Distance < r1r2)
	{
		Vector3 normalS1 = Vector3(worldPosS2 - worldPosS1);
		Vector3 normalS2 = Vector3(worldPosS1 - worldPosS2);
		float depth = r1r2 - Distance;

		CollisionPoint coll1(sphere2.entityID, depth, normalS1.Normalize());
		CollisionPoint coll2(sphere1.entityID, depth, normalS2.Normalize());
		coll1.collisionPoint = worldPosS1 + (worldPosS2 - worldPosS1).Normalize() * depth;
		coll2.collisionPoint = worldPosS2 + (worldPosS1 - worldPosS2).Normalize() * depth;

		std::lock_guard<std::mutex> lokcColl1(sphere1.collider.mutex);
		std::lock_guard<std::mutex> lokcColl2(sphere2.collider.mutex);

		sphere1.collider.CollisionPoint.push_back(coll2);
		sphere2.collider.CollisionPoint.push_back(coll1);

		LOG("Collision", STATELOG::NONE);
		return ;
	}

	return;
}



void ColliderSystem::CheckCollisionBoxSphere(BoxCollider& sphere1, SphereCollider& sphere2)
{
	return ;
}



Vector3 ColliderSystem::GetVertexBox(Transform& transform, const Vector3& halfLength, int vertexIndex)
{
	Vector3 vertex;

	double xSign = (vertexIndex & 1) == 0 ? 1.0 : -1.0;
	double ySign = (vertexIndex & 2) == 0 ? 1.0 : -1.0;
	double zSign = (vertexIndex & 4) == 0 ? 1.0 : -1.0;

	vertex.x = xSign * halfLength.x;
	vertex.y = ySign * halfLength.y;
	vertex.z = zSign * halfLength.z;

	Vector4 transformedVertex = transform.world * Vector4(vertex.x, vertex.y, vertex.z, 1.0);

	vertex = Vector3(transformedVertex.x, transformedVertex.y, transformedVertex.z);

	return vertex;
}

std::array<Vector3, 3> ColliderSystem::GetAxis(const std::array<Vector3, 8>& arrayOfVertices,const Transform& transfrom)
{

	std::array<Vector3, 3> output;
	Vector3 pos, rotation, scale;

	Matrix4X4::DecomposeMatrix(transfrom.world, pos, rotation, scale);

	Matrix4X4 rotationMatrix = Matrix4X4::RotationMatrix4X4(rotation);


	output[0] = static_cast<Vector3>(rotationMatrix * Vector4(0, 1, 0, 1));
	output[1] = static_cast<Vector3>(rotationMatrix * Vector4(0, 0, 1, 1));
	output[2] = static_cast<Vector3>(rotationMatrix * Vector4(1, 0, 0, 1));


	return output;
}

void ColliderSystem::ProjectVerticesOnAxis(const std::array<Vector3, 8>& verticiesArray, const Vector3& axis, float& outmin, float& outmax)
{
	// Make shure thaht this variable will be overwritten
	outmin = std::numeric_limits<float>::infinity();
	outmax = std::numeric_limits<float>::lowest();


	for (size_t i = 0; i < verticiesArray.size(); i++)
	{
		float projection = Vector3::DotProduct(verticiesArray[i], axis);

		if (projection < outmin)
			outmin = projection;

		if (projection > outmax)
			outmax = projection;

	}

}





Vector3 ColliderSystem::DeterminateVectorNormal(const Vector3& normal, const Vector3& origin)
{
	if (Vector3::DotProduct(origin, normal) >= 0.f)
		return normal;

	return -normal;
}


Vector3 GetClosestVertex(const std::array<Vector3, 8>& verticies1, const std::array<Vector3, 8>& verticies2) 
{
	Vector3 closestVertex = verticies1[0];

	float minDistance = std::numeric_limits<float>::infinity();

	for (const Vector3& vertex1 : verticies1)
	{
		float distance = Vector3::Distance(vertex1, verticies2[0]);

		if (distance < minDistance) {
			minDistance = distance;
			closestVertex = vertex1;
		}
	}

	return closestVertex;
}


void ColliderSystem::CheckCollisionBoxBox(BoxCollider& Box1, BoxCollider& Box2)
{
	Vector3 NormalCollision = Vector3::Zero();
	float depth = std::numeric_limits<float>::infinity();


	Entity* entity1 = m_currentScene->GetEntities(Box1.entityID);
	Entity* entity2 = m_currentScene->GetEntities(Box2.entityID);


	Transform& transformbox1 = *m_currentScene->GetComponent<Transform>(entity1);
	Transform& transformbox2 = *m_currentScene->GetComponent<Transform>(entity2);

	Vector3 halfLegnhtbox1 = Box1.Size;
	Vector3 halfLegnhtbox2 = Box2.Size;

	
	std::array<Vector3,8> cubeVerticies1;
	std::array<Vector3,8> cubeVerticies2;


	// Applie transformation to the cube 
	for (int i = 0; i < cubeVerticies1.size(); ++i) {
		cubeVerticies1[i] = GetVertexBox(transformbox1, halfLegnhtbox1, i);
		cubeVerticies2[i] = GetVertexBox(transformbox2, halfLegnhtbox2, i);
	}

	// Get Axis
	std::array<Vector3, 3> AxisCube1 = GetAxis(cubeVerticies1, transformbox1);
	std::array<Vector3, 3> AxisCube2 = GetAxis(cubeVerticies2, transformbox2);

	Vector3 ImpactPoint1;
	Vector3 ImpactPoint2;


	// Process SAT
	for (size_t i = 0; i < AxisCube1.size(); i++) {
	
			float maxA, minA, maxB, minB;
			// Project vertices on the axis for both cubes
			ProjectVerticesOnAxis(cubeVerticies1, AxisCube1[i], minA, maxA);
			ProjectVerticesOnAxis(cubeVerticies2, AxisCube1[i], minB, maxB);

			// Check for separation along the axis
			if (minA >= maxB || minB >= maxA)
			{
				return ;
			}

			float axisDepth = std::fminf(maxB - minA,maxA-minB);

			if(axisDepth < depth)
			{
				depth = axisDepth;
				NormalCollision = AxisCube1[i];
			}
			ImpactPoint1 = GetClosestVertex(cubeVerticies1, cubeVerticies2);
			ImpactPoint2 = GetClosestVertex(cubeVerticies2, cubeVerticies1);


	}
	
	
	// Process SAT
	for (size_t i = 0; i < AxisCube1.size(); i++) {
		float maxA, minA, maxB, minB;

		// Project vertices on the axis for both cubes
		ProjectVerticesOnAxis(cubeVerticies1, AxisCube2[i], minA, maxA);
		ProjectVerticesOnAxis(cubeVerticies2, AxisCube2[i], minB, maxB);

		// Check for separation along the axis
		if (minA >= maxB || minB >= maxA)
		{
			return ;
		}

		float axisDepth = std::fminf(maxB - minA, maxA - minB);

		if (axisDepth < depth)
		{
			depth = axisDepth;
			NormalCollision = AxisCube2[i];	

		}

		ImpactPoint1 = GetClosestVertex(cubeVerticies1, cubeVerticies2);
		ImpactPoint2 = GetClosestVertex(cubeVerticies2, cubeVerticies1);

	}

	
		depth /= NormalCollision.Norm();
		NormalCollision = NormalCollision.Normalize();

		CollisionPoint p1;
		p1.collisionPoint = ImpactPoint1;
		p1.depht = depth;
		p1.entityIDBeenCollidWith = Box2.entityID;
		p1.Normal = DeterminateVectorNormal(NormalCollision, transformbox1.world.GetPos());

		CollisionPoint p2;
		p2.collisionPoint = ImpactPoint2;
		p2.depht = depth;
		p2.entityIDBeenCollidWith = Box1.entityID;
		p2.Normal = DeterminateVectorNormal(NormalCollision, transformbox2.world.GetPos());



		
		Box1.collider.CollisionPoint.push_back(p1);
		Box2.collider.CollisionPoint.push_back(p2);
	


	return ;
}

