#include <vector>
#include <limits>
#include <ToolBoxMathHeaders.h>
#include "Vector4.h"
#include "Physics/Collider/ColliderSystem.hpp"
#include "Physics/Collider/SphereCollider.hpp"
#include "Physics/Collider/BoxCollider.hpp"
#include "Ressources/Scene/Scene.h"
#include "Core/DataStructure/Project.hpp"
#include "LowRenderer/Gizmo/Gizmo.hpp"

void ColliderSystem::Init(Scene* scene)
{
	currentScene = scene;

}

void ColliderSystem::Awake(Scene* scene)
{
	currentScene = scene;
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
			Vector3 transformPos = transform->World.GetPos();
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
			Vector3 transformPos = transform->World.GetPos();
			Gizmo::DrawBox(transform->World, boxptr->Size, GizmoColor::GREENGIZMO);

		}
	}



}

void ColliderSystem::FixedUpdate(Scene* scene)
{
	std::vector<SphereCollider>* dataSphere =  reinterpret_cast<std::vector<SphereCollider>*>(scene->GetComponentDataArray<SphereCollider>());
	std::vector<BoxCollider>* dataBox = reinterpret_cast<std::vector<BoxCollider>*>(scene->GetComponentDataArray<BoxCollider>());

	for (size_t i = 0; i < dataSphere->size(); i++)
	{
		SphereCollider* sphereptr = &(*dataSphere)[i];
		
		for (size_t k = 0; k < dataSphere->size(); k++)
		{
			SphereCollider* sphereptr2 = &(*dataSphere)[k];

			if (sphereptr == sphereptr2)
				continue;
			CheckCollision(*sphereptr, *sphereptr2);
		}

		for (size_t i = 0; i < dataBox->size(); i++)
		{
			BoxCollider* Boxptr = &(*dataBox)[i];
			CheckCollision(*Boxptr, *sphereptr);

		}

	}


	for (size_t i = 0; i < dataBox->size(); i++)
	{
		BoxCollider* Boxptr = &(*dataBox)[i];

		for (size_t k = 0; k < dataBox->size(); k++)
		{
			BoxCollider* Boxptr2 = &(*dataBox)[k];

			if (Boxptr == Boxptr2)
				continue;

			if(CheckCollision(*Boxptr, *Boxptr2))
			{
			}
		}


	}
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



bool ColliderSystem::CheckCollision(SphereCollider& sphere1, SphereCollider& sphere2)
{
	 Entity* entityID1 = currentScene->GetEntities(sphere1.entityID);
	 Entity* entityID2 = currentScene->GetEntities(sphere2.entityID);

	const Transform* s1 = currentScene->GetComponent<Transform>(entityID1);
	const Transform* s2 = currentScene->GetComponent<Transform>(entityID2);

	const Vector3 worldPosS1 = static_cast<const Vector3>(s1->World[3]);
	const Vector3 worldPosS2 = static_cast<const Vector3>(s2->World[3]);

	const float distance = Vector3::Distance(worldPosS1, worldPosS2);
	const float r1r2 = sphere1.radius + sphere2.radius;


	if (distance < r1r2)
	{
		CollisionPoint coll1;
		coll1.depht = distance;
		coll1.Normal = Vector3(worldPosS2 - worldPosS1).Normalize();

		CollisionPoint coll2;
		coll2.depht = distance;
		coll2.Normal = Vector3(worldPosS1 - worldPosS2).Normalize();
		
		sphere1.collider.CollisionPoint.push_back(coll1);
		sphere1.collider.CollisionPoint.push_back(coll2);

		LOG("Collision", STATELOG::NONE);
		return true;
	}

	return false;
}



bool ColliderSystem::CheckCollision(BoxCollider& sphere1, SphereCollider& sphere2)
{
	return false;
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

	Vector4 transformedVertex = transform.World * Vector4(vertex.x, vertex.y, vertex.z, 1.0);

	vertex = Vector3(transformedVertex.x, transformedVertex.y, transformedVertex.z);

	return vertex;
}

std::array<Vector3, 6> ColliderSystem::GetAxis(std::array<Vector3, 8> arrayOfVertices)
{
	std::array<Vector3, 6> output;

	int faceIndices[6][4] = {
	{0, 1, 2, 3}, // Front face (vertices: 0, 1, 2, 3)
	{5, 4, 7, 6}, // Back face (vertices: 4, 7, 6, 5)
	{0, 4, 5, 1}, // Top face (vertices: 0, 4, 5, 1)
	{4, 0, 1, 5}, // Bottom face (vertices: 2, 6, 7, 3)
	{0, 2, 6, 4}, // Left face (vertices: 0, 2, 6, 4)
	{1, 5, 7, 3}  // Right face (vertices: 1, 5, 7, 3)
	};


	for (int i = 0; i < 6; ++i) {
		// Calculate the normal vector for each face
			Vector3 v1 = arrayOfVertices[faceIndices[i][0]];
			Vector3 v2 = arrayOfVertices[faceIndices[i][1]];
			Vector3 v3 = arrayOfVertices[faceIndices[i][2]];
			Vector3 normal = (Vector3::CrossProduct(v2 - v1, v3 - v1)).Normalize();

			output[i] = normal;
	
	}

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





bool ColliderSystem::CheckCollision(BoxCollider& Box1, BoxCollider& Box2)
{
	Entity* entity1 = currentScene->GetEntities(Box1.entityID);
	Entity* entity2 = currentScene->GetEntities(Box2.entityID);


	Transform& transformbox1 = *currentScene->GetComponent<Transform>(entity1);
	Transform& transformbox2 = *currentScene->GetComponent<Transform>(entity2);

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
	std::array<Vector3, 6> AxisCube1 = GetAxis(cubeVerticies1);
	std::array<Vector3, 6> AxisCube2 = GetAxis(cubeVerticies2);

	

	// Process SAT // 

	// Axis cube 1 

	// Process SAT
	for (size_t i = 0; i < AxisCube1.size(); i++) {

		if( !(i  %  2))
		{
			float maxA, minA, maxB, minB;

			// Project vertices on the axis for both cubes
			ProjectVerticesOnAxis(cubeVerticies1, AxisCube1[i], minA, maxA);
			ProjectVerticesOnAxis(cubeVerticies2, AxisCube1[i], minB, maxB);

			// Check for separation along the axis
			if (minA >= maxB || minB >= maxA)
				return false;

		}
		
	}
	
	
	// Process SAT
	for (size_t i = 0; i < AxisCube1.size(); i++) {
		float maxA, minA, maxB, minB;

		// Project vertices on the axis for both cubes
		ProjectVerticesOnAxis(cubeVerticies1, AxisCube2[i], minA, maxA);
		ProjectVerticesOnAxis(cubeVerticies2, AxisCube2[i], minB, maxB);

		// Check for separation along the axis
		if (minA >= maxB || minB >= maxA)
			return false;
	}


	std::cout << "Collision " << std::endl;

	return true;
}