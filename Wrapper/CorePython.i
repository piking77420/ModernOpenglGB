%module CorePython

%{
	#include "../source/include/Core/DataStructure/Project.hpp"
	#include "../source/include/Core/Debug/LogClass.h"
	#include "../source/include/Core/ECS/Scene/PythonScript.h"
	#include "../source/include/Core/ECS/Component.h"
	#include "../source/include/Core/ECS/ECSComponent.h"
	#include "../source/include/Core/ECS/Entity.h"
	#include "../source/include/Core/ECS/IECSSystem.h"
	#include "../source/include/Core/ECS/PythonScript.h"
	#include "../source/include/Core/ECS/Register.h"


	#include "../source/include/Physics/Collider/BoxCollider.hpp"
	#include "../source/include/Physics/Collider/Collider.hpp"
	#include "../source/include/Physics/Collider/ColliderSystem.hpp"
	#include "../source/include/Physics/Collider/SphereCollider.hpp"

	#include "../source/include/Physics/GraphScene/GraphScene.h"
	#include "../source/include/Physics/PhysicsSystem/PhysicsSystem.hpp"
	#include "../source/include/Physics/RigidBody/RigidBody.h"
	#include "../source/include/Physics/Transform/Transform.hpp"

	// Define necessary typedefs and using statements here
    typedef uint32_t (*ECSComponentCreateFunction)(std::vector<uint8_t>& memory, Entity* entity, Component** ptr);
    typedef void(*ECSComponentFreeFunction)(Component* ptr);
    typedef std::string (*GetNameOfComponent)();
%}



%include <std_string.i>
%include <std_vector.i>

%include "../source/include/Core/ECS/Entity.h"
%include "../source/include/Core/ECS/Component.h"

%include "../source/include/Core/ECS/ECSComponent.h"

%template(EcsComponent_Transform) EcsComponent<Transform>;

%{
    // Initialize the static member variables for the EcsComponent class
    template<> const uint32_t EcsComponent<Transform>::componentTypeID = Component::RegisterComponent<Transform>(ECSComponentCreate<Transform>, ECSComponentFree<Transform>, sizeof(Transform), GetName<Transform>);
    template<> const size_t EcsComponent<Transform>::size = sizeof(Transform);
    template<> const ECSComponentCreateFunction EcsComponent<Transform>::CreateFunction = ECSComponentCreate<Transform>;
    template<> const ECSComponentFreeFunction EcsComponent<Transform>::FreeFunction = ECSComponentFree<Transform>;
    template<> const GetNameOfComponent EcsComponent<Transform>::NameFunction = GetName<Transform>;
%}

%template(EcsComponent_MeshRenderer) EcsComponent<MeshRenderer>;

%{
    // Initialize the static member variables for the EcsComponent class
    template<> const uint32_t EcsComponent<MeshRenderer>::componentTypeID = Component::RegisterComponent<MeshRenderer>(ECSComponentCreate<MeshRenderer>, ECSComponentFree<MeshRenderer>, sizeof(MeshRenderer), GetName<MeshRenderer>);
    template<> const size_t EcsComponent<MeshRenderer>::size = sizeof(MeshRenderer);
    template<> const ECSComponentCreateFunction EcsComponent<MeshRenderer>::CreateFunction = ECSComponentCreate<MeshRenderer>;
    template<> const ECSComponentFreeFunction EcsComponent<MeshRenderer>::FreeFunction = ECSComponentFree<MeshRenderer>;
    template<> const GetNameOfComponent EcsComponent<MeshRenderer>::NameFunction = GetName<MeshRenderer>;
%}


%template(EcsComponent_Rigidbody) EcsComponent<Rigidbody>;

%{
    // Initialize the static member variables for the EcsComponent class
    template<> const uint32_t EcsComponent<Rigidbody>::componentTypeID = Component::RegisterComponent<Rigidbody>(ECSComponentCreate<Rigidbody>, ECSComponentFree<Rigidbody>, sizeof(Rigidbody), GetName<Rigidbody>);
    template<> const size_t EcsComponent<Rigidbody>::size = sizeof(Rigidbody);
    template<> const ECSComponentCreateFunction EcsComponent<Rigidbody>::CreateFunction = ECSComponentCreate<Rigidbody>;
    template<> const ECSComponentFreeFunction EcsComponent<Rigidbody>::FreeFunction = ECSComponentFree<Rigidbody>;
    template<> const GetNameOfComponent EcsComponent<Rigidbody>::NameFunction = GetName<Rigidbody>;
%}

%template(EcsComponent_SphereCollider) EcsComponent<SphereCollider>;

%{
    // Initialize the static member variables for the EcsComponent class
    template<> const uint32_t EcsComponent<SphereCollider>::componentTypeID = Component::RegisterComponent<SphereCollider>(ECSComponentCreate<SphereCollider>, ECSComponentFree<SphereCollider>, sizeof(SphereCollider), GetName<SphereCollider>);
    template<> const size_t EcsComponent<SphereCollider>::size = sizeof(SphereCollider);
    template<> const ECSComponentCreateFunction EcsComponent<SphereCollider>::CreateFunction = ECSComponentCreate<SphereCollider>;
    template<> const ECSComponentFreeFunction EcsComponent<SphereCollider>::FreeFunction = ECSComponentFree<SphereCollider>;
    template<> const GetNameOfComponent EcsComponent<SphereCollider>::NameFunction = GetName<SphereCollider>;
%}
%template(EcsComponent_BoxCollider) EcsComponent<BoxCollider>;

%{
    // Initialize the static member variables for the EcsComponent class
    template<> const uint32_t EcsComponent<BoxCollider>::componentTypeID = Component::RegisterComponent<BoxCollider>(ECSComponentCreate<BoxCollider>, ECSComponentFree<BoxCollider>, sizeof(BoxCollider), GetName<BoxCollider>);
    template<> const size_t EcsComponent<BoxCollider>::size = sizeof(BoxCollider);
    template<> const ECSComponentCreateFunction EcsComponent<BoxCollider>::CreateFunction = ECSComponentCreate<BoxCollider>;
    template<> const ECSComponentFreeFunction EcsComponent<BoxCollider>::FreeFunction = ECSComponentFree<BoxCollider>;
    template<> const GetNameOfComponent EcsComponent<BoxCollider>::NameFunction = GetName<BoxCollider>;
%}

%template(EcsComponent_DirectionalLight) EcsComponent<DirectionalLight>;

%{
    // Initialize the static member variables for the EcsComponent class
    template<> const uint32_t EcsComponent<DirectionalLight>::componentTypeID = Component::RegisterComponent<DirectionalLight>(ECSComponentCreate<DirectionalLight>, ECSComponentFree<DirectionalLight>, sizeof(DirectionalLight), GetName<DirectionalLight>);
    template<> const size_t EcsComponent<DirectionalLight>::size = sizeof(DirectionalLight);
    template<> const ECSComponentCreateFunction EcsComponent<DirectionalLight>::CreateFunction = ECSComponentCreate<DirectionalLight>;
    template<> const ECSComponentFreeFunction EcsComponent<DirectionalLight>::FreeFunction = ECSComponentFree<DirectionalLight>;
    template<> const GetNameOfComponent EcsComponent<DirectionalLight>::NameFunction = GetName<DirectionalLight>;
%}

%template(EcsComponent_PointLight) EcsComponent<PointLight>;

%{
    // Initialize the static member variables for the EcsComponent class
    template<> const uint32_t EcsComponent<PointLight>::componentTypeID = Component::RegisterComponent<PointLight>(ECSComponentCreate<PointLight>, ECSComponentFree<PointLight>, sizeof(PointLight), GetName<PointLight>);
    template<> const size_t EcsComponent<PointLight>::size = sizeof(PointLight);
    template<> const ECSComponentCreateFunction EcsComponent<PointLight>::CreateFunction = ECSComponentCreate<PointLight>;
    template<> const ECSComponentFreeFunction EcsComponent<PointLight>::FreeFunction = ECSComponentFree<PointLight>;
    template<> const GetNameOfComponent EcsComponent<PointLight>::NameFunction = GetName<PointLight>;
%}

%template(EcsComponent_SpothLight) EcsComponent<SpothLight>;

%{
    // Initialize the static member variables for the EcsComponent class
    template<> const uint32_t EcsComponent<SpothLight>::componentTypeID = Component::RegisterComponent<SpothLight>(ECSComponentCreate<SpothLight>, ECSComponentFree<SpothLight>, sizeof(SpothLight), GetName<SpothLight>);
    template<> const size_t EcsComponent<SpothLight>::size = sizeof(SpothLight);
    template<> const ECSComponentCreateFunction EcsComponent<SpothLight>::CreateFunction = ECSComponentCreate<SpothLight>;
    template<> const ECSComponentFreeFunction EcsComponent<SpothLight>::FreeFunction = ECSComponentFree<SpothLight>;
    template<> const GetNameOfComponent EcsComponent<SpothLight>::NameFunction = GetName<SpothLight>;
%}


%include "../source/include/Core/ECS/IECSSystem.h"
%include "../source/include/Core/ECS/Register.h"
%include "../source/include/Core/DataStructure/Project.hpp"
%include "../source/include/Core/Debug/LogClass.h"
%include "../source/include/Core/ECS/PythonScript.h"




%include "../source/include/Physics/Collider/BoxCollider.hpp"
%include "../source/include/Physics/Collider/Collider.hpp"
%include "../source/include/Physics/Collider/ColliderSystem.hpp"
%include "../source/include/Physics/Collider/SphereCollider.hpp"

%include "../source/include/Physics/GraphScene/GraphScene.h"
%include "../source/include/Physics/PhysicsSystem/PhysicsSystem.hpp"
%include "../source/include/Physics/RigidBody/RigidBody.h"
%include "../source/include/Physics/Transform/Transform.hpp"

