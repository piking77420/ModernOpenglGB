#pragma once
#include <vector>
#include <stdint.h>

#define ComponentNULL 4294967295

class Entity
{
public:

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

private:

	uint32_t ID;

};

