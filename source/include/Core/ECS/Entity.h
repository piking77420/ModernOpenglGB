#pragma once
#include <vector>
#include <stdint.h>
#include <string>
#include "UI/InspectorSelectable.h"
#define ComponentNULL 4294967295
#define EntityNULL 4294967295


class Scene;

class Entity : public InspectorSelectable
{
public:


	void OnInspector() override;


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

	Scene* scene;
	std::vector< uint32_t> EnityComponents;
	uint32_t ID;

private:

};

