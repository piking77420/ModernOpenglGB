#include <vector>
#include "Entity.h"
#include <iostream>
#include "IECSSystem.h"
#include <unordered_map>
#include "ECSComponent.h"


class Component;
class Scene;

class Register
{
public:


	
	Entity* CreateEntity();
	Entity* GetEntities(uint32_t ID);

	template<class T>
	bool IsEntityHas(const Entity* entity);

	template<class T>
	T* TryGetComponent(const Entity* entity);

	template<class T>
	inline void AddComponent(Entity* entity)
	{
		AddComponentInternal(T::ComponentTypeID, entity);
	}

	template<class T>
	inline T* GetComponent(Entity* entity) 
	{
		return reinterpret_cast<T*>(GetComponentInternal(T::ComponentTypeID, entity));
	}
	
	template<class T>
	inline const T* GetComponent(const Entity* entity) const
	{
		return reinterpret_cast<const T*>(GetComponentInternal(T::ComponentTypeID, entity));
	}


	template<class T>
	inline void RemoveComponent(Entity* entity)
	{
		RemoveComponentInternal(T::ComponentTypeID, entity);
	}
	


	inline void RemoveEntity(Entity* entity)
	{
		RemoveEntityInternal(entity);
	}


	Register();
	~Register();

	std::vector<Entity*> entities;

	// ComponentType // DATA
	std::vector< std::pair<uint32_t, std::vector<uint8_t>* > > ComponentsData;

	std::vector<IEcsSystem*> Systems;

private:
	friend Scene;
	void AddComponentInternal(uint32_t ComponenTypeID,Entity* entity);
	Component* GetComponentInternal(uint32_t ComponenTypeID,Entity* entity);
	const Component* GetComponentInternal(uint32_t ComponenTypeID, const Entity* entity) const;



	void RemoveComponentInternal(uint32_t ComponenTypeID,Entity* entity);
	void RemoveEntityInternal(Entity* entity);

	
	void AddComponentEntitie(Entity* entity,uint32_t ComponenTypeID , uint32_t ComponentIndex);
	void RemoveComponentEntitie(Entity* entity, uint32_t ComponenTypeID);

	

};

template<class T>
inline bool Register::IsEntityHas(const Entity* entity)
{
	uint32_t ComponentID = T::ComponentTypeID;

	if (entity->EnityComponents[ComponentID] != ComponentNULL)
		return true;

	return false;
}

template<class T>
inline T* Register::TryGetComponent(const Entity* entity)
{
	if (!IsEntityHas<T>(entity))
		return nullptr;

	return entity->EnityComponents[T::ComponentID];
}
