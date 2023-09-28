#pragma once
#include<Mathf.h>
#include<Math/ToolBoxMathHeaders.h>
#define MAX_BONE_INFLUENCE 4


struct Vertex
{

	void SetPos(const Vector3 _Position);
	void SetNormal(const Vector3 _Position);
	void SetTextureCoord(const Vector2 _TextureCoord);

	Vector3 Position;
	Vector3 Normal;
	Vector2 TextureCoord;
	// tangent
	Vector3 Tangent;
	// bitangent
	Vector3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];

	Vertex(const Vector3& pos , const Vector3& normal , const Vector3 uv) : Position(pos) , Normal(normal) , TextureCoord(uv)
	{

	}

	Vertex()
	{

	}
};

