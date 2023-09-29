#pragma once 
#include "Component.h"


template<class T>
uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, Entity* entity, Component** ptr)
{
	uint32_t index = memory.size();
	memory.resize(index + T::size);
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

	static  inline uint32_t componentTypeID = 0;

	// Size_t Of the component
	static  const size_t size   ;
	// ONLY WORK ON C++ 17 or more


private:

	static inline const ECSComponentCreateFunction CreateFunction = ECSComponentCreate<T>;
	static  const GetNameOfComponent NameFunction;
	static  const ECSComponentFreeFunction FreeFunction;
};




template<class T>
const size_t EcsComponent<T>::size = sizeof(T);



template<class T>
const ECSComponentFreeFunction EcsComponent<T>::FreeFunction(ECSComponentFree<T>);

template<class T>
const GetNameOfComponent EcsComponent<T>::NameFunction(GetName<T>);



