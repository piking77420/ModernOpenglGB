#pragma once
#include "ToolBoxMathHeaders.h"
#include "Ressources/Model/Model.h"
class Projet;
class Shader;


class Gizmo
{
	
	static void DrawSphere(const Vector3& pos,float radius);
private:
	friend Projet;
	static const Shader* GizmoShader;
};

