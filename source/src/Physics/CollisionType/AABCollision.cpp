#include "Physics/CollisionType/AABCollision.h"
#include "Core/DataStructure/Entity/Entity.h"
#include <algorithm>

void AABCollision::ImguiWindow()
{

	

}

bool AABCollision::IsInside(Vector3 point, float radius)
{





	Matrix4X4 model = Matrix4X4().TRS(Vector3::Zero, Vector3::Zero, Size);
	std::vector<Vector3> vertex;


	Vector3 v1(1, 1, 1);

	
	for (size_t i = 0; i < mverticies.size(); i++)
	{
		Vector3 pos = ((mverticies[i]) * model);
		
		vertex.push_back(pos );
	}
	


	float VminZ = INFINITY;
	float VminY = INFINITY;
	float VminX = INFINITY;

	float VMaxZ = -INFINITY;
	float VMaxY = -INFINITY;
	float VMaxX = -INFINITY;

	for (size_t i = 0; i < vertex.size(); i++)
	{
		if (vertex[i].z < VminZ)
			VminZ = vertex[i].z;

		if (vertex[i].y < VminY)
			VminY = vertex[i].y;

		if (vertex[i].x < VminX)
			VminX = vertex[i].x;


		if (vertex[i].z > VMaxZ)
			VMaxZ = vertex[i].z;

		if (vertex[i].y > VMaxY)
			VMaxY = vertex[i].y;

		if (vertex[i].x > VMaxX)
			VMaxX = vertex[i].x;
	}

	Vector4 Scalemin = Vector3(VminX, VminY, VminZ);
	Vector4 Scalemax = Vector3(VMaxX, VMaxY, VMaxZ);



	Scalemin = Scalemin * Matrix4X4().TRS(Vector3::Zero, currentTranform->transform.GetRotation(), Vector3::One);
	Scalemax = Scalemax * Matrix4X4().TRS(Vector3::Zero, currentTranform->transform.GetRotation(), Vector3::One);



	Scalemin += currentTranform->transform.GetPos();
	Scalemax += currentTranform->transform.GetPos();

	


	Vector3 px;

	



	float minx = Mathf::minimum(point.x, Scalemax.x);	
	px.x = Mathf::maximum(Scalemin.x, minx);

	float miny = Mathf::minimum(point.y, Scalemax.y);
	px.y = Mathf::maximum(Scalemin.y, miny);

	float minz = Mathf::minimum(point.z, Scalemax.z);
	px.z = Mathf::maximum(Scalemin.z, minz);





	float distance = sqrtf( powf((px.x - point.x), 2) + powf((px.y - point.y), 2) + powf((px.z - point.z), 2));


	if(distance <= radius)
	{
		return true;
	}
	



	

	return false;
}



void AABCollision::Update(const Collider& collider)
{
	posMin = LocalposMin *  currentTranform->transform.m_GlobalMatrix ;
	posMax = LocalposMax * currentTranform->transform.m_GlobalMatrix;
	
	Midpos = LocalposMax - LocalposMin;

}

Vector3 AABCollision::GetNormal() const 
{
	Vector3 result = posMin.CrossProduct(posMax);

	if (currentTranform->transform.GetWordlPos().DotProduct(result) <= 0.f)
	{
		return posMax.CrossProduct(posMin);
	}
	return result;

	return Vector3();
}

float AABCollision::GetD(const Vector3& point) const
{
	Vector3 r = Midpos - point;


	Vector3 Normal = GetNormal();
	float d0 = r.DotProduct(Normal.Normalize());

	float result = -(d0 * Normal.Normalize().Norm());
	return result;
}

AABCollision::AABCollision(Entity& entity,std::vector<Vector3> verticies,Vector3& size) : CollisionType(entity)  ,Size(size)
{

	mverticies = verticies;
}


AABCollision::~AABCollision()
{
}
