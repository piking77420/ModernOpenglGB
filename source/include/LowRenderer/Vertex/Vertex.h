#pragma once
#include<Mathf.h>
#include<Math/ToolBoxMathHeaders.h>

class Vertex
{
public:

	void SetPos(const Vector3 _Position);
	void SetNormal(const Vector3 _Position);
	void SetTextureCoord(const Vector2 _TextureCoord);

	Vector3 Position;
	Vector3 Normal;
	Vector2 TextureCoord;
	Vector4 color;

	Vertex(const Vector3 _Position);

	Vertex(const Vector3 _Position , const Vector3 _Normal , const Vector2 _TextureCoord);
	Vertex();
	~Vertex();
};

