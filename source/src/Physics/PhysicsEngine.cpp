#include "Physics/PhysicsEngine.h"
#include "Collider/Collider.h"
#include <memory>


void PhysicsEngine::DeterminateNbrOfCollision()
{	
	
	if (allCollider.size() < 2)
		return;


	for (size_t i = 0; i < allCollider.size(); i++)
	{	
		Collider* c1 = allCollider[i];
		for (size_t k = i + 1; k < allCollider.size(); k++)
		{
			Collider* c2 = allCollider[k];
            CollisionDetection coll ;
            coll.collider1 = c1;
            coll.collider2 = c2;


			AllCollisions.push_back(coll);
				
		}
	}

	/*
	for (size_t i = 0; i < allColliderUi.size(); i++)
	{
		Collider* c1 = allColliderUi[i];
		for (size_t k = i + 1; k < allColliderUi.size(); k++)
		{
			Collider* c2 = allColliderUi[k];


			AllCollisionsUi.push_back(CollisionDetection(c1, c2));

		}
	}
	*/

}
void PhysicsEngine::UpdateColliders()
{
	DeterminateNbrOfCollision();
	UpdatePhysics();
	UpdateUi();
}
PhysicsEngine::PhysicsEngine()
{

}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::UpdatePhysics()
{
	for (size_t i = 0; i < AllCollisions.size(); i++)
	{
		for (size_t k = 0; k < AllCollisions[i].collider1->CollisionShape.size(); k++)
		{
			for (size_t j = 0; j < AllCollisions[i].collider2->CollisionShape.size(); j++)
			{
				SphereCollision* c1 = dynamic_cast<SphereCollision*>(AllCollisions[i].collider1->CollisionShape[k]);
				SphereCollision* c2 = dynamic_cast<SphereCollision*>(AllCollisions[i].collider2->CollisionShape[j]);
				PlaneCollision* p1 = dynamic_cast<PlaneCollision*>(AllCollisions[i].collider1->CollisionShape[k]);
				PlaneCollision* p2 = dynamic_cast<PlaneCollision*>(AllCollisions[i].collider2->CollisionShape[j]);
				AABCollision* q1 = dynamic_cast<AABCollision*>(AllCollisions[i].collider1->CollisionShape[k]);
				AABCollision* q2 = dynamic_cast<AABCollision*>(AllCollisions[i].collider2->CollisionShape[j]);

				BoxCollisionType* b1 = dynamic_cast<BoxCollisionType*>(AllCollisions[i].collider1->CollisionShape[k]);
				BoxCollisionType* b2 = dynamic_cast<BoxCollisionType*>(AllCollisions[i].collider2->CollisionShape[j]);


				CheckCollision(c1, b1);
				CheckCollision(c1, b2);

				CheckCollision(c2, b1);
				CheckCollision(c2, b2);


				CheckCollision(c1, q2);
				CheckCollision(c1, q1);
				CheckCollision(c1, q2);
				CheckCollision(c2, q1);
				CheckCollision(c2, q2);
				CheckCollision(c1, c2);
				CheckCollision(c2, p1);
				CheckCollision(c1, p1);
				CheckCollision(c2, p2);
				CheckCollision(c1, p2);
			}
		}

	}
	AllCollisions.clear();
}

void PhysicsEngine::UpdateUi()
{/*
	for (size_t i = 0; i < AllCollisionsUi.size(); i++)
	{
		for (size_t k = 0; k < AllCollisionsUi[i].collider1->CollisionShape.size(); k++)
		{
			for (size_t j = 0; j < AllCollisionsUi[i].collider2->CollisionShape.size(); j++)
			{
				SphereCollision* c1 = dynamic_cast<SphereCollision*>(AllCollisionsUi[i].collider1->CollisionShape[k]);
				SphereCollision* c2 = dynamic_cast<SphereCollision*>(AllCollisionsUi[i].collider2->CollisionShape[j]);
				PlaneCollision* p1 = dynamic_cast<PlaneCollision*>(AllCollisionsUi[i].collider1->CollisionShape[k]);
				PlaneCollision* p2 = dynamic_cast<PlaneCollision*>(AllCollisionsUi[i].collider2->CollisionShape[j]);
				AABCollision* q1 = dynamic_cast<AABCollision*>(AllCollisionsUi[i].collider1->CollisionShape[k]);
				AABCollision* q2 = dynamic_cast<AABCollision*>(AllCollisionsUi[i].collider2->CollisionShape[j]);
				CheckCollision(c1, q2);
				CheckCollision(c1, q1);
				CheckCollision(c1, q2);
				CheckCollision(c2, q1);
				CheckCollision(c2, q2);
				CheckCollision(c1, c2);
				CheckCollision(c2, p1);
				CheckCollision(c1, p1);
				CheckCollision(c2, p2);
				CheckCollision(c1, p2);
			}
		}

	}
	AllCollisionsUi.clear();*/
}

void PhysicsEngine::CheckCollision(SphereCollision* sphere1, AABCollision* quad1)
{



	if (!sphere1 || !quad1)
	{
		return;
	}
	Vector3 spherePos = sphere1->currentTranform->transform.GetWordlPos();


	
		if (quad1->IsInside(spherePos, sphere1->radius))
		{
			sphere1->IsCollided(*quad1->currentTranform);
			quad1->IsCollided(*sphere1->currentTranform);
		}
	


}

void  PhysicsEngine::CheckCollision(SphereCollision* sphere1, SphereCollision* sphere2)
{
	


	if (!sphere1 || !sphere2)
	{
			return ;
	}

	Vector3 selftPos = sphere1->currentTranform->transform.GetWordlPos();
	Vector3 otherspherepos = sphere2->currentTranform->transform.GetWordlPos();

	float distance = (otherspherepos - selftPos ).Norm();

	float r1r2 = sphere1->radius + sphere2->radius;
	if (distance < r1r2)
	{
		sphere1->IsCollided(*sphere2);
		sphere2->IsCollided(*sphere1);
	}


}
void PhysicsEngine::CheckCollision(PlaneCollision* plane1, PlaneCollision* plane2)
{
	return ;
}
void PhysicsEngine::CheckCollision(SphereCollision* sphere1, PlaneCollision* plane1)
{

	if (!sphere1 || !plane1 )
	{
		return ;
	}
	Vector3 spherePos = sphere1->currentTranform->transform.GetWordlPos();
	

	if(!plane1->IsInfinite)
	{
		if(plane1->IsInside(spherePos,sphere1->radius))
		{
			sphere1->IsCollided(*plane1->currentTranform);
			plane1->IsCollided(*sphere1->currentTranform);
		}
	}
	else
	{
		float checkDistance = plane1->GetDistanceFromPlane(spherePos);
		if (checkDistance < sphere1->radius)
		{
			sphere1->IsCollided(*plane1->currentTranform);
			plane1->IsCollided(*sphere1->currentTranform);
			return;
		}
	}



}


// Here TO DO	

void PhysicsEngine::CheckCollision(SphereCollision* sphere1, BoxCollisionType* box)
{

	if (!sphere1 || !box)
	{
		return;
	}

	float radius = sphere1->radius;
	Vector3 point = sphere1->currentTranform->transform.GetWordlPos();

	for (size_t i = 0; i < box->m_BoxFaces.size(); i++)
	{
		Vector3 normal = box->m_BoxFaces[i].Normal;
			
		Vector3 vectorDirector = -(normal.Normalize() * radius);

		float d0 = box->m_BoxFaces[i].WP0.DotProduct(normal.Normalize());
		float d = -(d0 * normal.Norm());	

		float t0 = -(point.DotProduct(normal) + d) / vectorDirector.DotProduct(normal);

		if (t0 < 0 || t0 > 1)
			continue;

		Vector3 intersectionPoint = (point + vectorDirector * t0);

		// Pivot de Gauss // 
		
		Vector3 u = box->m_BoxFaces[i].WP1;	
		Vector3 v = box->m_BoxFaces[i].WP2;

		float s,t;
		
		Matrix matrix = Matrix(3, 3);

		

		if (box->m_BoxFaces[i].Axe == RIGHT)
		{
			matrix[0][0] = u.z;
			matrix[0][1] = v.z;
			matrix[0][2] = intersectionPoint.z;

			matrix[1][0] = u.y;
			matrix[1][1] = v.y;
			matrix[1][2] = intersectionPoint.y;
		}
		else if (box->m_BoxFaces[i].Axe == UP)
		{
			matrix[0][0] = u.x;
			matrix[0][1] = v.x;
			matrix[0][2] = intersectionPoint.x;

			matrix[1][0] = u.z;
			matrix[1][1] = v.z;
			matrix[1][2] = intersectionPoint.z;
		}
		else if (box->m_BoxFaces[i].Axe == FORWARD)
		{
			matrix[0][0] = u.x;
			matrix[0][1] = v.x;
			matrix[0][2] = intersectionPoint.x;

			matrix[1][0] = u.y;
			matrix[1][1] = v.y;
			matrix[1][2] = intersectionPoint.y;
		}

		matrix = matrix.PivotDeGauss();
		
		//std::cout << matrix << std::endl;


		t = matrix[0][2];
		s = matrix[1][2];
		
		t = Mathf::Abs(t);
		s = Mathf::Abs(s);



		if((t <= 1 && t >= 0 ) && (s <= 1 && s >= 0))
		{
			sphere1->IsCollided(*box->currentTranform);
			box->IsCollided(*sphere1->currentTranform);
		}
	}



}
