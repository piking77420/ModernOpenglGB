#pragma once
#include <vector>
#include <stdint.h>
#include <string>
#include "UI/InspectorSelectable.h"
#define ComponentNULL 4294967295

class Register;

class Entity : public InspectorSelectable
{
public:

	std::string Entityname;

	uint32_t& SetID()
	{
		return ID;
	}

	uint32_t GetID()
	{
		return ID;
	}

	Entity();
	~Entity()
	{
		
	};


	std::vector< uint32_t> EnityComponents;
	uint32_t ID;
	Register* Scene_register;

private:


};

