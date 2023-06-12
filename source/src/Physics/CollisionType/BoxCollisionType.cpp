#include "Physics/CollisionType/BoxCollisionType.h"
#include "Ressources/Model/Model.h"
#include "Mathf.h"





void BoxCollisionType::Update(const Collider& collider)
{	
	


	for (size_t i = 0; i < m_BoxFaces.size(); i++)
	{
		Vector3 posWorld = currentTranform->transform.GetWordlPos();
		Vector3 Rotate = currentTranform->transform.rotate;
		Vector3 scale = currentTranform->transform.scale;
		Matrix4X4 model = Matrix4X4().TRS(posWorld, Rotate, scale);
		

		std::cout << m_BoxFaces[i].WP1 << std::endl;

		m_BoxFaces[i].WP0 = (m_BoxFaces[i].P0 + posWorld) * model;
		m_BoxFaces[i].WP1 = (m_BoxFaces[i].P1 + posWorld )* model;
		m_BoxFaces[i].WP2 = (m_BoxFaces[i].P2 + posWorld )* model;
		m_BoxFaces[i].Normal = GetNormal(m_BoxFaces[i]);
	}


}

Vector3 BoxCollisionType::GetNormal(const Faces& faces)
{
	// Origin of cube

	Vector3 result = faces.P1.CrossProduct(faces.P2);

	if ( faces.P0.DotProduct(result) <= 0.f)
	{
		return faces.P2.CrossProduct(faces.P1);
	}


	return result;
}

BoxCollisionType::BoxCollisionType(Entity& entity) : CollisionType(entity)
{
	SetFaces();
}

BoxCollisionType::~BoxCollisionType()
{
}

void BoxCollisionType::SetFaces()
{

	// Bot 
	Vector3 BotP0 = Vector3(-1, -1, -1);
	Vector3 BotP1 = Vector3(2, 0, 0);
	Vector3 BotP2 = Vector3(0, 0, 2);
	Faces Bot(BotP0, BotP1, BotP2, UP);
	// Top;
	Vector3 TopP0 = Vector3(-1, 1, -1);
	Vector3 TopP1 = Vector3(2, 0, 0);
	Vector3 TopP2 = Vector3(0, 0, 2);	
	Faces Top(TopP0, TopP1, TopP2, UP);

	// Left 
	Vector3 LeftP0 = Vector3(-1, -1, -1);
	Vector3 LeftP1 = Vector3(0, 0, 2);
	Vector3 LeftP2 = Vector3(0, 2, 0);
	Faces Left(LeftP0, LeftP1, LeftP2, RIGHT);

	// Right 
	Vector3 RightP0 = Vector3(1, -1, -1);
	Vector3 RightP1 = Vector3(0, 0, 2);
	Vector3 RightP2 = Vector3(0, 2, 0);
	Faces Right(RightP0, RightP1, RightP2, RIGHT);


	// Front 
	Vector3 FrontP0 = Vector3(-1, -1, 1);
	Vector3 FrontP1 = Vector3(2, 0, 0);
	Vector3 FrontP2 = Vector3(0, 2, 0);
	Faces Front(FrontP0, FrontP1, FrontP2, FORWARD);


	// Back 
	Vector3 BackP0 = Vector3(-1, -1, -1);;
	Vector3 BackP1 = Vector3(2, 0, 0);
	Vector3 BackP2 = Vector3(0, 2, 0);
	Faces Back(BackP0, BackP1, BackP2, FORWARD);

	//m_BoxFaces.push_back(Bot);
	//m_BoxFaces.push_back(Top);
	m_BoxFaces.push_back(Left);
	//m_BoxFaces.push_back(Right);
	//m_BoxFaces.push_back(Front);
	//m_BoxFaces.push_back(Back);
}

Faces::Faces(const Vector3& _P0, const Vector3& _P1, const Vector3& _P2, const Axes _Axe)
{
	P0 = _P0;
	P1 = _P1;
	P2 = _P2;
	Axe = _Axe;
}
