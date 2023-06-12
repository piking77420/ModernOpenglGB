#include "Physics/CollisionType/PlaneCollision.h"
#include "Collider/Collider.h"


bool PlaneCollision::IsInside(const Vector3& point)
{
	Vector3 normal = GetNormalOffPlane();

	Vector3 segment = point - normal;

	/*
	if (normal.DotProduct(point) != 0.f)
		return false;
		*/

	// Point
	float lerp = -(m_P0.DotProduct(normal) + GetD(point)) / point.DotProduct(normal);
		
	if (lerp >= 0 && lerp <= 1)
	{
	}
	
		

	//if(point == m_P0 + m_P1 + m_P2)
	


	return false;
}

bool PlaneCollision::IsInside(Vector3 point, float radius)
{
	Vector3 normal = GetNormalOffPlane();
	Vector3 vectorDirector = -(normal.Normalize() * radius);


	// Sphere segment // 
	float t0 = -(point.DotProduct(normal) + GetD(point)) / vectorDirector.DotProduct(normal);
	if (t0 < 0 && t0 > 1)
	{
		return false;
	}
	Vector3 intersectionPoint = (point + vectorDirector * t0) ;

	/*
	// tu //

	Vector3 VectorDirectorP1 =  m_P1 - m_P0;

	float t1 = -(point.DotProduct(normal) + GetD(point)) / VectorDirectorP1.DotProduct(normal);


	// sv //

	Vector3 VectorDirectorP2 = m_P2 - m_P0;
	float t2 = -(point.DotProduct(normal) + GetD(point)) / VectorDirectorP2.DotProduct(normal);
	*/


	// std::cout << " t1 = " << t1 << " " << "t2 = " << t2 << std::endl;

	/*
	Matrix test = Matrix(2);
	test[0][0] = 2;
	test[0][1] = 0;

	test[1][0] = 0;
	test[1][1] = 1;

	Vector v = Vector(3.f,2.f);
	*/
	//test = test.ReturnInv();


	


	// equation ax + bx + cz + d
	float value = normal.Normalize().DotProduct(intersectionPoint) + GetD(point);

	if (value >= 0 && value <= 1)
	{
		// std::cout <<  value << std::endl;

		return true;
	}



	//if(point == m_P0 + m_P1 + m_P2)



	return false;
}


Vector3 PlaneCollision::GetNormalOffPlane() const
{
	Vector3 result = m_P1.CrossProduct(m_P2);

	if (m_P0.DotProduct(result) <= 0.f)
	{
		return m_P2.CrossProduct(m_P1);
	}
	return result;
}

float PlaneCollision::GetDistanceFromPlane(const Vector3& point) const
{
	
	Vector3 normal = GetNormalOffPlane();

	float d = GetD(point);


	Vector3 r = m_P0 - point;	

	float distance = (r.DotProduct(normal.Normalize()));


	return Mathf::Abs(distance);
}


float PlaneCollision::GetD(const Vector3& point) const
{
	Vector3 Normal = GetNormalOffPlane();
	float d0 = m_P0.DotProduct(Normal.Normalize());

	float result = -(d0 * Normal.Norm());

	return result;
}


	PlaneCollision::PlaneCollision()
{
	//m_P0 = currentTranform->transform.GetWordlPos();
	//m_P1 = Vector3::Right;
	//m_P2 = Vector3::Forward;
}




void PlaneCollision::ImguiWindow()
{
	ImGui::DragFloat3("V1", m_P1.SetPtr());
	ImGui::DragFloat3("V2", m_P2.SetPtr());

}

void PlaneCollision::Update(const Collider& collider)
{
	m_P0 = collider.EntityAttachTo->transform.GetWordlPos();
}

PlaneCollision::PlaneCollision(Entity& _currentTransform, const Vector3& _P1, const Vector3& _P2, bool _IsInfinit) : IsInfinite(_IsInfinit)
{
	m_P0 = _currentTransform.transform.GetWordlPos();
	currentTranform = &_currentTransform;



	m_P1 = _P1;
	m_P2 = _P2;
}


PlaneCollision::PlaneCollision(Entity& _currentTransform, bool _IsInfinit) : m_P1((Vector3::Right)), m_P2((Vector3::Forward)) , IsInfinite(_IsInfinit)
{
	m_P0 = _currentTransform.transform.GetWordlPos();
	currentTranform = &_currentTransform;
}


PlaneCollision::PlaneCollision(Entity& _currentTransform) : m_P1((Vector3::Right)) , m_P2((Vector3::Forward)) , IsInfinite(false)
{

	m_P0 = _currentTransform.transform.GetWordlPos();
	currentTranform = &_currentTransform;
}

PlaneCollision::~PlaneCollision()
{
}

