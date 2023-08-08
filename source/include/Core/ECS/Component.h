#pragma once
#include <stdint.h>
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <string>
#include <vector>
#include "Entity.h"


class Register;
class Component;

typedef uint32_t (*ECSComponentCreateFunction)(std::vector<uint8_t>& memory, Entity* entity, Component** ptr);
typedef void(*ECSComponentFreeFunction)(Component* ptr);
typedef std::string (*GetNameOfComponent)();


class Component
{



private:

	static inline std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t, std::string> >* ComponentTypeInfos = new  std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t, std::string> >();

public:
	virtual ~Component() {}
	virtual void ImguiWindowComponent() { std::cout << "Bacis Imgui ImguiWindowComponent !! " << std::endl; };

	bool IsEnable = true;
	uint32_t entityID;
	
	
protected:
	static uint32_t GetNbrOfComponent()
	{
		return Component::ComponentTypeInfos->size();
	}

	template<typename T>
	static  uint32_t RegisterComponent(ECSComponentCreateFunction createfn,
		ECSComponentFreeFunction freefn, size_t size, GetNameOfComponent namefn)
	{

		// Which array all the data of all this type Componenet will be 
		uint32_t DataArrayIndex = ComponentTypeInfos->size();
		ComponentTypeInfos->push_back({ createfn,freefn,size, namefn() });

		return DataArrayIndex;
	}

	friend Entity;
private:
	static inline ECSComponentCreateFunction GetCreateFN(uint32_t ID)
	{
		return std::get<0>(ComponentTypeInfos->at(ID));
	}

	static inline ECSComponentFreeFunction GetFreeFN(uint32_t ID)
	{
		return std::get<1>(ComponentTypeInfos->at(ID));
	}

	static inline size_t GetSizeOfComponent(uint32_t ID)
	{
		return std::get<2>(ComponentTypeInfos->at(ID));
	}
	static inline std::string GetComponentName(uint32_t ID)
	{
		return std::get<3>(ComponentTypeInfos->at(ID));
	}
	friend Register;

protected:


};

