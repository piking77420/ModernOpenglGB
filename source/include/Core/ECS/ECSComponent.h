#pragma once 
#include "Component.h"


template<class T>
uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, Entity* entity, Component** ptr)
{
	uint32_t index = memory.size();
	memory.resize(index + T::SIZE);
	T* component = new(&memory[index]) T();
	component->entityID = entity->ID;
	*ptr = component;
	return index;
}

template<class T>
constexpr std::string GetName()
{
	std::string rawname = typeid(T).name();
	std::string name;
	for (size_t i = 6; i < rawname.size(); i++)
	{
		name.push_back(rawname[i]);
	}


	return name;
}


template<class T>
void ECSComponentFree(Component* ptr)
{
	T* component = (T*)ptr;
	component->~T();
}




template<class T>
class EcsComponent : public Component
{
public:

	static  const uint32_t ComponentTypeID;

	// Size_t Of the component
	static  const size_t SIZE;
	// ONLY WORK ON C++ 17
	// TO DO RegisterComponent<EcsComponent<T> OR T






private:

	static  const ECSComponentCreateFunction CREATE_FUNCTION;
	static  const GetNameOfComponent NAME_FUNCTION;
	static  const ECSComponentFreeFunction FREE_FUNCTION;
};


template<class T>
const uint32_t EcsComponent<T>::ComponentTypeID(Component::RegisterComponent<T>(ECSComponentCreate<T>, ECSComponentFree<T>, sizeof(T), GetName<T>));

template<class T>
const size_t EcsComponent<T>::SIZE(sizeof(T));

template<class T>
const ECSComponentCreateFunction EcsComponent<T>::CREATE_FUNCTION(ECSComponentCreate<T>);

template<class T>
const ECSComponentFreeFunction EcsComponent<T>::FREE_FUNCTION(ECSComponentFree<T>);

template<class T>
const GetNameOfComponent EcsComponent<T>::NAME_FUNCTION(GetName<T>);



#define MONOBEHAVIOUR(x) : public EcsComponent<x>