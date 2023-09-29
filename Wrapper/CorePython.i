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
    #include "../source/include/Core/ECS/Scene.h"


	#include "../source/include/Physics/Collider/BoxCollider.hpp"
	#include "../source/include/Physics/Collider/Collider.hpp"
	#include "../source/include/Physics/Collider/ColliderSystem.hpp"
	#include "../source/include/Physics/Collider/SphereCollider.hpp"

	#include "../source/include/Physics/GraphScene/GraphScene.h"
	#include "../source/include/Physics/PhysicsSystem/PhysicsSystem.hpp"
	#include "../source/include/Physics/RigidBody/RigidBody.h"
	#include "../source/include/Physics/Transform/Transform.hpp"



	#include "../source/include/Core/Math/Vector2.h"
    #include "../source/include/Core/Math/Vector3.h"
    #include "../source/include/Core/Math/Vector4.h"
    #include "../source/include/Core/Math/Matrix2X2.h"
    #include "../source/include/Core/Math/Matrix3X3.h"
    #include "../source/include/Core/Math/Matrix4X4.h"

    #include "../source/include/LowRenderer/Cam/Camera.h"



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
%include "../source/include/Core/ECS/Register.h"

%template(EcsComponent_Transform) EcsComponent<Transform>;
%template(EcsComponent_BoxCollider) EcsComponent<BoxCollider>;
%template(EcsComponent_Rigidbody) EcsComponent<Rigidbody>;
%template(EcsComponent_SphereCollider) EcsComponent<SphereCollider>;



// Define wrapper functions for each component type
Transform* GetComponent_Transform(Entity* entity) {
    return reinterpret_cast<Transform*>(m_registerScene.GetComponentInternal(Transform::componentTypeID, entity));
}

BoxCollider* GetComponent_BoxCollider(Entity* entity) {
    return reinterpret_cast<BoxCollider*>(m_registerScene.GetComponentInternal(BoxCollider::componentTypeID, entity));
}

Rigidbody* GetComponent_Rigidbody(Entity* entity) {
    return reinterpret_cast<Rigidbody*>(m_registerScene.GetComponentInternal(Rigidbody::componentTypeID, entity));
}

SphereCollider* GetComponent_SphereCollider(Entity* entity) {
    return reinterpret_cast<SphereCollider*>(m_registerScene.GetComponentInternal(SphereCollider::componentTypeID, entity));
}

%include "../source/include/Core/ECS/Scene.h"



%include "../source/include/Core/ECS/IECSSystem.h"
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




%include "../source/include/Core/Math/Vector2.h"
%include "../source/include/Core/Math/Vector3.h"
%include "../source/include/Core/Math/Vector4.h"
%include "../source/include/Core/Math/Matrix2X2.h"
%include "../source/include/Core/Math/Matrix3X3.h"
%include "../source/include/Core/Math/Matrix4X4.h"


%extend Vector2 {

	  float __getitem__(int index) const {
        if (index == 0) return $self->x;
        if (index == 1) return $self->y;
        return 0.0;
    }

      void __setitem__(int index, float value) {
        if (index == 0) $self->x = value ;
        if (index == 1) $self->y = value;
    }
}


%extend Vector3 {
   float __getitem__(int index) const {
        if (index == 0) return $self->x;
        if (index == 1) return $self->y;
        if (index == 2) return $self->z;
        return 0.0;
    }

      void __setitem__(int index, float value) {
        if (index == 0) $self->x = value ;
        if (index == 1) $self->y = value;
        if (index == 2) $self->z = value;
    }

}

%extend Vector4 {

      float __getitem__(int index) const {
        if (index == 0) return $self->x;
        if (index == 1) return $self->y;
        if (index == 2) return $self->z;
        if (index == 2) return $self->w;

        return 0.0;
    }

      void __setitem__(int index, float value) {
        if (index == 0) $self->x = value ;
        if (index == 1) $self->y = value;
        if (index == 2) $self->z = value;
        if (index == 2) $self->w = value;
    }
    %rename(toVector2) operator Vector2;
}


    %include "../source/include/LowRenderer/Cam/Camera.h"
