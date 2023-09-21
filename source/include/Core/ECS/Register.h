#include <vector>
#include "Entity.h"
#include "IECSSystem.h"
#include "ECSComponent.h"
#include <functional>


class Component;
class Scene;

class Register
{
public:

	Register();
	~Register();

	std::vector<Entity*> entities;

	// ComponentType // DATA
	std::vector< std::pair<uint32_t, std::vector<uint8_t>* >> ComponentsData;

	std::vector<IEcsSystem*> systems;

	std::vector<std::function<void(IEcsSystem& system, uint32_t ComponentTypeID,std::vector<uint8_t>* datavector) >> OnReSizeDataVector;

private:
	friend Scene;
	void AddComponentInternal(uint32_t ComponenTypeID,Entity* entity);
	Component* GetComponentInternal(uint32_t ComponenTypeID,Entity* entity);
	const Component* GetComponentInternal(uint32_t ComponenTypeID, const Entity* entity) const;
	
	Entity* GetEntiesById(uint32_t entityId);

	void RemoveComponentInternal(uint32_t ComponenTypeID,Entity* entity);
	void RemoveEntityInternal(Entity* entity);

	void AddComponentEntity(Entity* entity,uint32_t ComponenTypeID , uint32_t ComponentIndex);
	void RemoveComponentEntity(Entity* entity, uint32_t ComponenTypeID);

	
	void AddSystemInternal(IEcsSystem* system);

	void TriggerOnresizeDataEvent(uint32_t ComponenTypeID,std::vector<uint8_t>* data);

};

