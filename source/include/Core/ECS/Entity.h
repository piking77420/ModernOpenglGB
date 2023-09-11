#pragma once
#include <vector>
#include <stdint.h>
#include <string>
#include "UI/InspectorSelectable.h"
#include "Core/ISerialzable/ISerialzable.h"
#define ComponentNULL 4294967295
#define EntityNULL 4294967295


class Scene;

class Entity : public InspectorSelectable , public ISerialzable
{
public:


	void OnInspector() override;
	void OnSerialize(Scene* scene) const override;
	void OnDeSerialize(Scene* scene) const override;

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

	Scene* scene = nullptr;
	std::vector< uint32_t> EnityComponents;
	uint32_t ID = EntityNULL;

private:

};

