#pragma once
#include "ToolBoxMathHeaders.h"
#include "Ressources/Mesh/Mesh.h"
#include "Core/DataStructure/Project.hpp"
class Shader;

enum class GizmoColor
{
	REDGIZMO,
	GREENGIZMO,
	BLUEGIZMO

};

class Gizmo
{
public:

	static void InitGizmo(const Project& projet);

	static void DrawSphere(const Vector3& pos,float radius,GizmoColor gizmoColor);
	static void DrawBox(const Matrix4X4& model,const Vector3& sizeBox, GizmoColor gizmoColor);

private:
	static inline const Mesh* Sphere = nullptr;
	static inline const Mesh* Box = nullptr;
	static inline const Shader* GizmoShader = nullptr;
	static  constexpr Vector4 GetColor(GizmoColor gizmoColor)
	{
		switch (gizmoColor)
		{
		case GizmoColor::REDGIZMO:
			return Vector4(1, 0, 0, 1);
			break;
		case GizmoColor::GREENGIZMO:
			return Vector4(0, 1, 0, 1);
			break;
		case GizmoColor::BLUEGIZMO:
			return Vector4(0, 0, 1, 1);
			break;
		default:
			break;
		}
	}
};

