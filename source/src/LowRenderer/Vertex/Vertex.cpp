#include <LowRenderer/Vertex/Vertex.h>


void Vertex::SetPos(const Vector3 _Position)
{
	Position = _Position;
}

void Vertex::SetNormal(const Vector3 _Normal)
{
	Normal = _Normal;
}

void Vertex::SetTextureCoord(const Vector2 _TextureCoord)
{
	TextureCoord = _TextureCoord;
}

Vertex::Vertex(const Vector3 _Position, const Vector3 _Normal, const Vector2 _TextureCoord) : Position(_Position) , Normal(_Normal) , TextureCoord(_TextureCoord) , color(Vector4::One())
{

}
Vertex::Vertex(const Vector3 _Position) : Position(_Position),color(Vector4::One())
{
	Normal = Vector3::One();
	TextureCoord = Vector2::One();

}



Vertex::Vertex() : Position(Vector3::One()), Normal(Vector3::One()), TextureCoord(Vector2::One()) , color(Vector4::One())
{
}

Vertex::~Vertex()
{
}
