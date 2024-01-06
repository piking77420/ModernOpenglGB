#pragma once
#include<string> 
#include <Math/ToolBoxMathHeaders.h>
#include "Ressources/Texture/Texture.hpp"

template<class T, typename T2>
struct PBRnode
{
	using MAP = T;
	using COEFF = T2;


	const MAP* ressourceMap;
	COEFF coeff;

	PBRnode<T, T2>()
	{
		ressourceMap = nullptr;
	}

	


};



struct MaterialPBR
{
	PBRnode<Texture, Vector3> albedo;

	PBRnode<Texture, float> metallic;

	PBRnode<Texture, float> specular;

	PBRnode<Texture, float> roughness;

	PBRnode<Texture, float> ao;


	PBRnode<Texture, bool> normal;

};