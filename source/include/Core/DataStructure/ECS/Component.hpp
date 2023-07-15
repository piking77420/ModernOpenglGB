#pragma once
#include <vector>
#include <tuple>

class Entity;

struct BaseComponent;
typedef int(*ECSComponentCreateFunction)(std::vector<BaseComponent*>* memory, Entity* entity);
typedef void (*ECSComponentFreeFunction)(BaseComponent* comp);

#define NULL_ENTITY_HANDLE nullptr


struct BaseComponent
{
public:
	//static uint32_t NextId();
	static uint32_t Register(ECSComponentCreateFunction create , ECSComponentFreeFunction free , size_t size);
	Entity* entity = NULL_ENTITY_HANDLE;
	inline static ECSComponentCreateFunction GetCreateFunction(uint32_t id)
	{
		return std::get<0>(componentsType[id]);
	}

	inline static ECSComponentFreeFunction GetFreeFunction(uint32_t id)
	{
		return std::get<1>(componentsType[id]);
	}

	inline static size_t GetSize(uint32_t id)
	{
		return std::get<2>(componentsType[id]);
	}

	inline static bool IsValid(uint32_t id)
	{
		return id < componentsType.size();
	}

private:
	static std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>> componentsType;
};

template<typename T>
struct ECSComponent : public BaseComponent
{
	static const  ECSComponentCreateFunction CREATE;
	static const  ECSComponentFreeFunction FREE;
	static const uint32_t ID;
	static size_t SIZE;
};





template<typename Component>
uint32_t ECSComponentCreate(std::vector<BaseComponent>* memory, Entity* entity)
{
	int index = memory.size();
	Component* component = new Component(*(Component*)comp);
	memory->push_back(component);
	component->entity = entity;
	return index;
}

template<typename Component>
void ECSComponentFree(BaseComponent* comp)
{
	Component* component = (Component*)comp;
	component->~Component();
}

template<typename T>
uint32_t const ECSComponent<T>::ID(BaseComponent::Register(ECSComponentCreate<T>, ECSComponentFree<T>,sizeof(T)));

template<typename T>
size_t ECSComponent<T>::SIZE = sizeof(T);


template<typename T>
const ECSComponentCreateFunction ECSComponent<T>::CREATE(ECSComponentCreate<T>);


template<typename T>
const ECSComponentFreeFunction ECSComponent<T>::FREE(ECSComponentFree<T>);

