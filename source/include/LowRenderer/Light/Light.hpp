#pragma once
#include "Core/Math/ToolBoxMathHeaders.h"


class Shader;
#define MAX_POINTLIGHT
#define MAX_SPOTHLIGHT

struct Light 
{
	Vector4 ambiantColor = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	Vector4 diffuseColor = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	Vector4 specularColor = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
	float SpecularStrengt = 32.f;

};

