#pragma once
#include "Ressources/Model/Model.h"


class Model;
class Shader;
class Scene;

class Gizmo
{
public:	

	Vector3 size;
	Vector4 color = Vector4::One();
	virtual void Render(Shader* shaderProgramm, Scene* scene){};
	//Gizmo(Collider* collider);
	virtual ~Gizmo();

protected:
	Model* model;

};
