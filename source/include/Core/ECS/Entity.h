#pragma once
#include <vector>
#include <stdint.h>
#include <string>
#include "UI/InspectorSelectable.h"
#include "Core/ISerialzable/ISerialzable.h"

#define ComponentNULL 4294967295
#define EntityNULL  4294967295

class Scene;

class Entity : public ISerialzable
{
public:


	static void OnInspector(uint32_t entityID, Scene* scene);
	void OnSerialize(Scene* scene) const override;
	void OnDeSerialize(Scene* scene) override;

	std::string entityName;

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

	Scene* scene = nullptr;
	std::vector< uint32_t> entityComponents;
	uint32_t ID = EntityNULL;
	
};

